FROM ubuntu:latest
WORKDIR /src
ENV BUILD_TYPE=Release
RUN apt-get update && apt-get -y install build-essential cmake libxxf86vm-dev libxtst-dev libxrandr-dev libxinerama-dev libxcursor-dev lcov libglu1-mesa-dev mesa-common-dev
COPY . .
RUN rm -rf ./build && cmake -B ./build -DCMAKE_BUILD_TYPE=${BUILD_TYPE}
RUN cmake --build ./build --config ${BUILD_TYPE}
RUN cd ./build && ctest -VV -C ${BUILD_TYPE}
