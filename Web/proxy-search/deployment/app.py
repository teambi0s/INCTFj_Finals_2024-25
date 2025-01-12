from flask import Flask, render_template, request, abort
import requests
from urllib.parse import urlparse
import ipaddress

app = Flask(__name__)

FLAG = "inctfj{localhost_only_access}" 

BLACKLISTED_HOSTNAMES = ["localhost", "127.0.0.1", "0.0.0.0",]
BLACKLISTED_IP_RANGES = [
    ipaddress.ip_network("10.0.0.0/8"),
    ipaddress.ip_network("172.16.0.0/12"),
    ipaddress.ip_network("192.168.0.0/16"),
    ipaddress.ip_network("169.254.0.0/16"),
    ipaddress.ip_network("::1/128"),
    ipaddress.ip_network("fc00::/7"),
    ipaddress.ip_network("fe80::/10")
]

def is_ip_blacklisted(host):
    try:
        ip = ipaddress.ip_address(host)
        for network in BLACKLISTED_IP_RANGES:
            if ip in network:
                return True
        return False
    except ValueError:
        return False
    except Exception as e:
        app.logger.error(f"Error checking IP blacklist: {e}")
        return False

def is_url_safe(target_url):
    try:
        parsed_url = urlparse(target_url)

        if parsed_url.scheme not in ["http", "https"]:
            return False

        hostname = parsed_url.hostname
        if hostname in BLACKLISTED_HOSTNAMES:
            return False

        if is_ip_blacklisted(hostname):
            return False

        return True
    except Exception:
        return False

@app.route("/")
def home():
    return render_template("index.html")

@app.route("/proxy")
def proxy():
    target_url = request.args.get("url")
    if not target_url:
        return "No URL provided", 400

    if not is_url_safe(target_url):
        app.logger.warning(f"Blocked unsafe URL: {target_url}")
        return "Blocked unsafe URL", 400

    try:
        response = requests.get(target_url, allow_redirects=False)
        response.raise_for_status()
        print(response.status_code)
        if response.status_code > 299 and response.status_code < 400:
            raise requests.RequestException("Redirects are not allowed")
        return response.text, response.status_code, {"Content-Type": response.headers.get("Content-Type", "text/html")}
    except requests.RequestException as e:
        app.logger.error(f"Error fetching URL {target_url}: {e}")
        return f"Error fetching the URL: {target_url}", 500

@app.route("/flag")
def flag():
    if request.remote_addr == "127.0.0.1" or request.remote_addr == "::1":
        return FLAG
    else:
        app.logger.warning(f"Unauthorized access attempt from {request.remote_addr}")
        abort(403)

if __name__ == "__main__":
    app.run(debug=False, host="0.0.0.0", port=1337)
