IMAGE_NAME = minimalist_chat_client_image
CONTAINER_NAME = minimalist_chat_client_container
NETWORK_NAME = minimalist_chat_network

build:
	docker build -t $(IMAGE_NAME) .

SERVER_IP = $(shell docker inspect -f '{{range .NetworkSettings.Networks}}{{.IPAddress}}{{end}}' minimalist_chat_server_container)

up: build
	docker run --rm -it \
		--name $(CONTAINER_NAME) \
		--network $(NETWORK_NAME) \
		$(IMAGE_NAME) ./myapp $(SERVER_IP) 8080

down:
	docker stop $(CONTAINER_NAME) || true

clean:
	docker rm $(CONTAINER_NAME) || true

restart: down up

status:
	docker ps -f name=$(CONTAINER_NAME)
