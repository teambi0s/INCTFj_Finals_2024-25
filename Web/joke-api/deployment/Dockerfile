FROM python:3.9-slim

WORKDIR /app

RUN apt-get update && apt-get install -y openssl

RUN openssl genrsa -out private_rsa.pem 2048 && \
    openssl rsa -in private_rsa.pem -traditional -out private.pem && \
    openssl rsa -in private_rsa.pem -traditional -pubout -out public_rsa.pem && \
    openssl rsa -in public_rsa.pem -pubin -RSAPublicKey_out -out public.pem

RUN rm private_rsa.pem public_rsa.pem

COPY . .

RUN pip install -r requirements.txt

EXPOSE 1337

CMD ["python", "app.py"]

