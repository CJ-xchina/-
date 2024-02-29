set(LLVM_LINK_COMPONENTS
  support
  FrontendOpenMP
  )

add_clang_library(clangTidyUcasSaatModule
  HelloWorldCheck.cpp
  NoCompareOnPointerTypes202328015059001Check.cpp
  NoDupNameFromStd202328015059001Check.cpp
  NoRegisterVar202328015059001Check.cpp
  NoSetjmpOrLongjmp202328015059001Check.cpp
  NoUnnamedInnerStruct202328015059001Check.cpp
  NoVoidPointer202328015059001Check.cpp
  TooManyNestedLevelsOfStruct202328015059001Check.cpp
  UcasSaatTidyModule.cpp

  LINK_LIBS
  clangTidy
  clangTidyCppCoreGuidelinesModule
  clangTidyUtils

  DEPENDS
  omp_gen
  )

clang_target_link_libraries(clangTidyUcasSaatModule
  PRIVATE
  clangAnalysis
  clangAnalysisFlowSensitive
  clangAnalysisFlowSensitiveModels
  clangAST
  clangASTMatchers
  clangBasic
  clangLex
  clangTooling
  clangTransformer
  )
