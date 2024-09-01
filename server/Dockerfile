# docker build -t server:1.0 .\server\ --progress=plain
# docker run --rm -p 3000:3000 server:1.0

FROM gcc:14.2.0 as builder

WORKDIR /app
COPY server.cpp .
# If not "-static" then you need to copy over .so to scratch
RUN g++ -o server server.cpp -static -Wl,--verbose
# CMD [ "./simple-server" ]

# To reduce image size
# ---
FROM scratch
COPY --from=builder /app/server .
ENTRYPOINT [ "/server" ]
# ---

# For documentation only, need to use "-p 3000:3000" on run
EXPOSE 3000