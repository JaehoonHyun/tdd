# Build binary
FROM golang:1.14 AS builder
WORKDIR /build

ENV CGO_ENABLED=0
ENV GO111MODULE=off 

COPY ./ ./
WORKDIR /build/remote-debugging-tdd
# RUN go mod download

# -gcflags "all=-N -l"로 컴파일러 최적화 옵션을 끈다.
RUN go build -gcflags "all=-N -l" -o calc .
RUN ls -al /build
RUN cp ./calc /bin/

# Install delve
# install go debugger
RUN go get -u github.com/go-delve/delve/cmd/dlv
RUN ls -al /go/bin/dlv

RUN cp /go/bin/dlv /bin/ 
EXPOSE 8000
EXPOSE 2345 
ENTRYPOINT ["/bin/dlv", "--listen=:2345", "--headless=true", "--api-version=2", "--accept-multiclient", "exec", "/bin/calc", "--continue"] 