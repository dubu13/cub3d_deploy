# Create setup_emscripten.sh
echo '#!/bin/bash
source ~/emsdk/emsdk_env.sh
exec "$@"' > setup_emscripten.sh
chmod +x setup_emscripten.sh