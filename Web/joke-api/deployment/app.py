import json
import jwt
import random
import os
from flask import Flask, request, jsonify, render_template

app = Flask(__name__)

with open('private.pem', 'rb') as f:
    PRIVATE_KEY = f.read()
with open('public.pem', 'rb') as f:
    PUBLIC_KEY = f.read()

SECRET_JOKE = "inctfj{Why do programmers prefer dark mode? Because light attracts bugs!}"

def get_token_from_header():
    auth_header = request.headers.get('Authorization')
    if not auth_header or not auth_header.startswith('Bearer '):
        return None, {"error": "Authorization header is missing or invalid."}

    token = auth_header.split(" ")[1]
    return token, None

def sanitize_joke_type(joke_type):
    app.logger.warning(f"Path: {os.getcwd()}")
    safe_joke_type = os.path.basename(joke_type)
    return safe_joke_type

@app.route('/')
def home():
    return render_template('index.html')

@app.route('/docs')
def docs():
    return render_template('docs.html')

@app.route('/generate_token', methods=['POST'])
def generate_token():
    data = request.json
    username = data.get("username", None)
    if not username:
        return jsonify({"error": "Username is required"}), 400

    try:
        token = jwt.encode(
            {"username": username, "admin": False},
            PRIVATE_KEY,
            algorithm='RS256'
        )
        return jsonify({"token": token.decode('utf-8')}), 200
    except Exception as e:
        return jsonify({"error": str(e)}), 500

@app.route('/jokes', methods=['GET'])
def get_joke():
    token, error = get_token_from_header()
    if error:
        return jsonify(error), 401

    joke_type = request.args.get('type', 'general.json')
    
    joke_type = sanitize_joke_type(joke_type)

    app.logger.warning(f"Type: {joke_type}")

    try:
        with open(f"/app/{joke_type}", 'r') as f:
            file_content = f.read()

        try:
            jokes = json.loads(file_content)
        except json.JSONDecodeError as e:
            app.logger.warning(f"Content: {file_content}")
            return jsonify({"error": f"JSON parsing error: {str(e)}", "file_content": file_content}), 400

    except FileNotFoundError:
        return jsonify({"error": f"Jokes of type '{joke_type}' not found."}), 404

    try:
        decoded = jwt.decode(token, PUBLIC_KEY, algorithms=['HS256', 'RS256'])
    except Exception as e:
        return jsonify({"error": str(e)}), 401

    if "admin" in decoded and decoded["admin"]:
        return jsonify({"joke": f"Top secret joke: {SECRET_JOKE}"})
    elif "username" in decoded:
        username = decoded["username"]
        random_joke = random.choice(list(jokes.values()))
        return jsonify({"joke": f"Welcome {username}, here's a joke: {random_joke}"})
    else:
        return jsonify({"error": "Invalid session, goodbye."}), 403

if __name__ == '__main__':
    app.run(debug=False, host='0.0.0.0', port=1337)
