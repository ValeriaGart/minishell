# Use a base image with a C compiler and standard libraries
FROM debian:buster

# Install necessary dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    libreadline-dev \
    libncurses-dev \
    git \
    valgrind

# Copy your project files into the Docker image
WORKDIR /usr/src/minishell
COPY . .

# Build your project
RUN make all

# Set the command to run your application
CMD ["/bin/bash"]
