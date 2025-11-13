FROM ubuntu:22.04 AS builder
RUN apt-get update && apt-get install -y \
    build-essential cmake git libssl-dev ca-certificates && rm -rf /var/lib/apt/lists/*

WORKDIR /src
COPY . /src
RUN cmake -S . -B build && cmake --build build -j$(nproc)

FROM ubuntu:22.04
RUN apt-get update && apt-get install -y ca-certificates && rm -rf /var/lib/apt/lists/*
COPY --from=builder /src/build/crow_dashboard /usr/local/bin/crow_dashboard
COPY src/dashboard.html /usr/share/crow/dashboard.html
EXPOSE 9999
CMD ["/usr/local/bin/crow_dashboard"]

