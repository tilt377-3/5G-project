FROM gcc:latest AS builder

WORKDIR /app
COPY client.cpp .

RUN g++ -static -O2 client.cpp -o client

FROM alpine:latest

WORKDIR /app

COPY --from=builder /app/client .

ENTRYPOINT ["./client"]