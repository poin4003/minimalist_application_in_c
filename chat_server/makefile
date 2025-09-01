IMAGE_NAME = minimalist_chat_server_image
CONTAINER_NAME = minimalist_chat_server_container
NETWORK_NAME = minimalist_chat_network

STATIC_DIR = ./resource

build:
	docker build -t $(IMAGE_NAME) .

up: build
	docker run --rm -it \
		--name $(CONTAINER_NAME) \
		--network $(NETWORK_NAME) \
		-v $(STATIC_DIR):/resource \
		-p 8080:8080 \
		$(IMAGE_NAME)

down:
	docker stop $(CONTAINER_NAME) || true

clean:
	docker rm $(CONTAINER_NAME) || true

restart: down up

status:
	docker ps -f name=$(CONTAINER_NAME)
