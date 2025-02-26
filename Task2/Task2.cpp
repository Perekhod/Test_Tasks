/*
************** ЗАДАНИЕ **************
Есть класс CodeGenerator, который умеет генерить код на разных языках.
Предложите рефакторинг с учетом, что количество языков будет расширяться
*/

class CodeGenerator {
public:
    enum Lang { JAVA, C_PLUS_PLUS, PHP };

    CodeGenerator (Lang language) { _language = language; }

    std::string generateCode () {
        switch (_language) {
            case JAVA:        //return generated java code
            case C_PLUS_PLUS: //return generated C++ code
            case PHP:         //return generated PHP code
        }
        throw new std::logic_error ("Bad language");
    }

    std::string someCodeRelatedThing () // used in generateCode()
    {
        switch (_language) {
            case JAVA:        //return generated java-related stuff
            case C_PLUS_PLUS: //return generated C++-related stuff
            case PHP:         //return generated PHP-related stuff
        }
        throw new std::logic_error ("Bad language");
    }

private:
    Lang _language;
};

/* __________Предложенное решение__________ */
#include <iostream>
#include <memory>
#include <stdexcept>

/* Базовый класс для генерации кода */
class CodeGenerator {
public:
    virtual ~CodeGenerator () = default;
    virtual std::string generateCode () = 0;
    virtual std::string someCodeRelatedThing () = 0;
};

/* Генерация кода для Java */
class JavaCodeGenerator : public CodeGenerator {
public:
    std::string generateCode () override {
        return "Generated Java code";
    }

    std::string someCodeRelatedThing () override {
        return "Java-related stuff";
    }
};

/* Генерация кода для C++ */
class CppCodeGenerator : public CodeGenerator {
public:
    std::string generateCode () override {
        return "Generated C++ code";
    }

    std::string someCodeRelatedThing () override {
        return "C++-related stuff";
    }
};

/* Генерация кода для PHP */
class PhpCodeGenerator : public CodeGenerator {
public:
    std::string generateCode () override {
        return "Generated PHP code";
    }

    std::string someCodeRelatedThing () override {
        return "PHP-related stuff";
    }
};

/* Создание генераторов кода */
class CodeGeneratorFactory {
public:
    enum Lang { JAVA, C_PLUS_PLUS, PHP };

    /* Делаем функцию статик, чтобы не создавать объект класса */
    static std::unique_ptr<CodeGenerator> createGenerator (Lang language) {
        switch (language) {
            case JAVA:        return std::make_unique<JavaCodeGenerator> ();
            case C_PLUS_PLUS: return std::make_unique<CppCodeGenerator> ();
            case PHP:         return std::make_unique<PhpCodeGenerator> ();
            default:          throw std::logic_error ("Unsupported language");
        }
    }
};

int main (void) {
    auto generatorJAVA = CodeGeneratorFactory::createGenerator (CodeGeneratorFactory::JAVA);
    std::cout << generatorJAVA->generateCode ()         << std::endl;
    std::cout << generatorJAVA->someCodeRelatedThing () << std::endl;

    auto generatorPHP = CodeGeneratorFactory::createGenerator (CodeGeneratorFactory::PHP);
    std::cout << generatorPHP->generateCode ()          << std::endl;
    std::cout << generatorPHP->someCodeRelatedThing ()  << std::endl;

    return 0;
}