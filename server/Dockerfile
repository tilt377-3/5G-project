FROM gcc:latest AS builder

WORKDIR /app
COPY server.cpp .

RUN g++ -static -O2 server.cpp -o server

FROM alpine:latest

WORKDIR /app

RUN apk add --no-cache netcat-openbsd

COPY --from=builder /app/server .

EXPOSE 8080/udp

HEALTHCHECK --interval=10s --timeout=3s --start-period=3s --retries=3 \
  CMD echo "ping" | nc -w 1 -u 127.0.0.1 8080 | grep -q "ping" || exit 1

ENTRYPOINT ["./server"]
