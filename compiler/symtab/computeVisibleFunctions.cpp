#include "computeVisibleFunctions.h"
#include "stmt.h"
#include "expr.h"


class GetClassMethods : public SymtabTraversal {
 public:
  Vec<FnSymbol*>* classMethods;
  GetClassMethods::GetClassMethods(Vec<FnSymbol*>* init_classMethods);
  void processSymbol(Symbol*);
};


GetClassMethods::GetClassMethods(Vec<FnSymbol*>* init_classMethods) {
  classMethods = init_classMethods;
}


void GetClassMethods::processSymbol(Symbol* sym) {
  if (TypeSymbol* type_sym = dynamic_cast<TypeSymbol*>(sym)) {
    if (StructuralType* class_type = dynamic_cast<StructuralType*>(type_sym->type)) {
      if (!class_type->value) {
        forv_Vec(FnSymbol, method, class_type->methods) {
          while (method) {
            classMethods->add(method);
            method = method->overload;
          }
        }
        FnSymbol* constructor = class_type->defaultConstructor;
        while (constructor) {
          classMethods->add(constructor);
          constructor = constructor->overload;
        }
      }
    }
  }
}


void ComputeVisibleFunctions::run(void) {
  classMethods.clear();
  GetClassMethods* traversal = new GetClassMethods(&classMethods);
  traversal->run();
  SymtabTraversal::run();
}


void ComputeVisibleFunctions::preProcessScope(SymScope* scope) {
  scope->setVisibleFunctions(&classMethods);
}
