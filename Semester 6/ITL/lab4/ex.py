class Human:
    species="H.sapiens"
    def __init__(self,name):
        self.name=name
        self.age=0

    def say(self,msg):
        print("{name}:{message}".format(name=self.name,message=msg))

    def sing(self):
        return 'yo... yo... microphone check... one two... one two...'
    
    def get_species(cls):
        return cls.species
    
    def grunt():
        return "*grunt*"
    
    def age(self):
        return self._age
    
    def age(self,age):
        self._age=age

    def age(self):
        del self._age


if __name__=='__main__':
    i=Human(name="Ian")
    i.say("hi")
    
    j = Human("Joel")
    j.say("hello")

    i.say(i.get_species()) # "Ian: H. sapiens"
    # Change the shared attribute
    Human.species = "H. neanderthalensis"
    i.say(i.get_species()) # => "Ian: H. neanderthalensis"
    j.say(j.get_species()) # => "Joel: H. neanderthalensis"
    # Call the static method
    print(Human.grunt()) # => "*grunt*"
    # Cannot call static method with instance of object
    # because i.grunt() will automatically put "self" (the object i) as an argument
    print(i.grunt()) # => TypeError: grunt() takes 0 positional arguments but 1 was given
    # Update the property for this instance
    i.age = 42 #Get the property
    i.say(i.age) # => "Ian: 42"
    j.say(j.age) # => "Joel: 0"
    # Delete the property del i.age
    # i.age # => this would raise an AttributeError