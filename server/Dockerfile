FROM gcc:latest AS builder

WORKDIR /app
COPY server.cpp .

RUN g++ -static -O2 server.cpp -o server

FROM alpine:latest

WORKDIR /app

RUN apk add --no-cache netcat-openbsd

COPY --from=builder /app/server .

EXPOSE 8080/udp

HEALTHCHECK --interval=30s --timeout=5s --start-period=5s --retries=3 \
  CMD nc -z -u 127.0.0.1 8080 || exit 1

ENTRYPOINT ["./server"]