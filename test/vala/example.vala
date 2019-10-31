// An example of using inheritance in Vala
// This just uses overloading

class Animal : Object {
	public virtual void run() {
		stdout.printf("Animal running\n");
	}
}

class Dog : Animal {
	public override void run() {
		stdout.printf("Dog running\n");
	}
}

int main() {
	Animal a = new Animal();
	// should print "Animal running"
	a.run();
	Animal d = new Dog();
	// should print "Dog running"
	d.run();
	return 0;
}