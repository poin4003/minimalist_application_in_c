IMAGE_NAME = minimalist_web_server_image
CONTAINER_NAME = minimalist_web_server_container

STATIC_DIR = ./resource

build:
	docker build -t $(IMAGE_NAME) .

up: build
	docker run --rm -d --name $(CONTAINER_NAME) -p 8080:8080 -v $(STATIC_DIR):/resource $(IMAGE_NAME)

down:
	docker stop $(CONTAINER_NAME) || true

clean:
	docker rm $(CONTAINER_NAME) || true

restart: down up

status:
	docker ps -f name=$(CONTAINER_NAME)
