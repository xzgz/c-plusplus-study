#include <iostream>

class Animal {
 public:
  virtual void eat() { std::cout << "Animal-->eat.\n"; }
};

class Mammal : public virtual Animal {
 public:
  virtual void eat() { std::cout << "Mammal-->eat.\n"; }
  virtual void breathe() { std::cout << "Mammal-->breathe.\n"; }
};

class WingedAnimal : public virtual Animal {
 public:
  virtual void eat() { std::cout << "WingedAnimal-->eat.\n"; }
  virtual void flap() { std::cout << "WingedAnimal-->flap.\n"; }
};

// A bat is a winged mammal
class Bat : public Mammal, public WingedAnimal {
// public:
//  virtual void eat() { std::cout << "Bat-->eat.\n"; }
  void eat() { std::cout << "Bat-->eat.\n"; }
};


class Animal2 {
 public:
  virtual void eat() { std::cout << "Animal2-->eat.\n"; }
};

class Mammal2 : protected virtual Animal2 {
 public:
  virtual void eat() { std::cout << "Mammal-->eat.\n"; }
  virtual void breathe() { std::cout << "Mammal-->breathe.\n"; }
};

class WingedAnimal2 : protected virtual Animal2 {
 public:
  virtual void eat() { std::cout << "WingedAnimal-->eat.\n"; }
  virtual void flap() { std::cout << "WingedAnimal-->flap.\n"; }
};

class Bat2 : public Mammal2, public WingedAnimal2 {
  void eat() { std::cout << "Bat2-->eat.\n"; }
};


int main() {
  Mammal animal_mammal = static_cast<Mammal>(*(new Bat()));
  WingedAnimal animal_wingedanimal = static_cast<WingedAnimal>(*new Bat());
  Animal *animal = new Bat();
  animal_mammal.eat();
  animal_wingedanimal.eat();
  animal->eat();

//  Animal2 *animal2 = new Bat2();  // error: ‘Animal’ is an ambiguous base of ‘Bat2’
//  animal2->eat();
}
