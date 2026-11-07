# Alexa Make a Joke

A simple C++ program that mimics Alexa telling a random joke.

## How it works
- Asks the user if they want to hear a joke
- If yes, picks a random joke from `randomJokes.txt` and displays the setup and punchline
- If no, exits with a friendly message

## Files
- `alexa_joke.cpp` — main program
- `randomJokes.txt` — joke database (one joke per line, format: `Setup?Punchline`)

## How to run
```bash
g++ alexa_joke.cpp -o alexa_joke
./alexa_joke
```

## Example
```
Alexa: Do you want to hear a joke? (yes/no): yes
Alexa: Why did the developer go broke?
Alexa: Because he used up all his cache.
```
