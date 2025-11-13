FROM ubuntu:22.04 AS builder

# Install build dependencies
RUN apt-get update && apt-get install -y \
    build-essential cmake git libssl-dev ca-certificates && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /src
COPY . /src

# ✅ Clean old CMake cache (fixes: "CMakeCache.txt directory mismatch")
RUN rm -rf build && cmake -S . -B build && cmake --build build -j$(nproc)

# --- Runtime image ---
FROM ubuntu:22.04
RUN apt-get update && apt-get install -y ca-certificates && \
    rm -rf /var/lib/apt/lists/*

# Copy compiled binary from builder
COPY --from=builder /src/build/crow_dashboard /usr/local/bin/crow_dashboard

# ✅ Copy HTML template so Crow can render it
COPY src/dashboard.html /usr/share/crow/dashboard.html

# Expose Crow port
EXPOSE 9999

# Start app
CMD ["/usr/local/bin/crow_dashboard"]

