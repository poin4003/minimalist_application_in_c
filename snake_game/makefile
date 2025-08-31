IMAGE_NAME = minimalist_snake_game_image
CONTAINER_NAME = minimalist_snake_game_container

build:
	docker build -t $(IMAGE_NAME) .

up: build
	docker run --rm -it --name $(CONTAINER_NAME) $(IMAGE_NAME)

down:
	docker stop $(CONTAINER_NAME) || true

clean:
	docker rm $(CONTAINER_NAME) || true

restart: down up

status:
	docker ps -f name=$(CONTAINER_NAME)