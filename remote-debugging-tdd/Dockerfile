# Build binary
FROM golang:1.13 AS builder
WORKDIR /build

ENV CGO_ENABLED=0

COPY go.mod ./
RUN go mod download

COPY . ./
RUN go build .

# Run on scratch
FROM alpine:3.10
WORKDIR /bin

COPY --from=builder /build/calc /bin/

EXPOSE 8000
ENTRYPOINT ["/bin/calc"]