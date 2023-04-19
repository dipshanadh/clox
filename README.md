# Clox

> Lox is a dynamically typed, interpreted scripting language. It was designed by Bob Nystrom for his book Crafting Interpreters.

The goal of this project is to implement Lox programming language using features built into C with the help of the book "Crafting Interpreters".

I am currently following along, but I hope I will be able to add my own features as well.

## Usage

To clone and run this application, you'll need Git and GCC installed on your computer. From your command line:

```bash
# Clone the repository
git clone https://github.com/dipshanadh/clox.git
cd clox
gcc -Isrc ./src/*.c -o clox && ./clox hello.lox
```

It should output `-117`.

## Thanks

Thanks to Bob Nystrom for the amazing book!
