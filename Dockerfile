# Use a base image with a minimal Linux distribution
FROM ubuntu:20.04

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive

# Update package lists and install required packages
RUN apt-get update -y && \
    apt-get install -y \
    build-essential \
    cmake \
    g++-11 \
    libeigen3-dev \
    git \
    libzmqpp-dev

# # Set the default compiler to GCC 11
# RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 100 && \
#     update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-11 100
