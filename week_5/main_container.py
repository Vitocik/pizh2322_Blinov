from class_container import ComplexContainer

if __name__ == "__main__":
    c = ComplexContainer()
    c.add(1 + 2j)
    c.add(3 - 4j)
    print(c)  # Вывод: [(1+2j), (3-4j)]
    c.save("complex_container.json")
    
    new_c = ComplexContainer()
    new_c.load("complex_container.json")
    print(new_c)  # Вывод: [(1+2j), (3-4j)]