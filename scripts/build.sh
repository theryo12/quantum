BUILD_DIR="build"
SCRIPT_DIR=$(dirname "$0")
PROJECT_DIR="${SCRIPT_DIR}/.."

if [ ! -d "$PROJECT_DIR/$BUILD_DIR" ]; then
    mkdir "$PROJECT_DIR/$BUILD_DIR"
fi

cd "$PROJECT_DIR/$BUILD_DIR"

cmake ..
make -j$(nproc)

if [ $? -eq 0 ]; then
    echo "Success!"
else
    echo "Error!"
    exit 1
fi
