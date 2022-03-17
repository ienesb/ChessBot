# ChessBot

## Installation

```bash
git clone https://github.com/ienesb/ChessBot.git
cd ChessBot
mkdir build
cd build
cmake -DCMAKE_PREFIX_PATH=`python -c 'import torch;print(torch.utils.cmake_prefix_path)'` ..
cmake --build . --config Release
make 
./chess
```

## Train model with custom dataset
Place your game{i}.txt files in the folder ai/games/
# never try to push dataset to remote!!!
