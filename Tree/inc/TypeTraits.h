#ifndef TYPETRAITS_H
#define TYPETRAITS_H

template <typename TypeParam>
class TypeTraits{
private:
   
   template <typename T>
   struct Traits{
      typedef T Type;
      enum{
         isPointer = false,
         isConst   = false,
         isRef     = false,
         isRRef    = false
      };
   };
   
   
   // const specialization
   template <typename T>
         struct Traits<const T>{ 
      typedef T Type;
      enum{
         isPointer = false,
         isConst   = true,
         isRef     = false,
         isRRef    = false
      };
         };
   
   // pointer specialization
   template <typename T>
   struct Traits<T *>{ 
      typedef T Type;
      enum{
         isPointer = true,
         isConst   = false,
         isRef     = false,
         isRRef    = false
      };
   };
   
   // pointer to const specialization
   template <typename T>
   struct Traits<T const *>{ 
      typedef T Type;
      enum{
         isPointer = true,
         isConst   = true,
         isRef     = false,
         isRRef    = false
      };
   };
   
   // reference specialization
   template <typename T>
   struct Traits<T &>{ 
      typedef T Type;
      enum{
         isPointer = false,
         isConst   = false,
         isRef     = true,
         isRRef    = false
      };
   };
   
   // rvalue reference specialization needed
   
   TypeTraits(TypeTraits const &other);
   
   
   struct Char2{
      char data[2];
   };
   
   template <typename ClassType>
   static Char2 fun(void (ClassType::*)());
   
   template <typename NonClassType>
   static char fun(...);
   
public:
   
   typedef typename Traits<TypeParam>::Type ValueType;
   typedef ValueType *PtrType;
   typedef ValueType &RefType;
   
   enum{
      isPointerType         = Traits<TypeParam>::isPointer,
      isReferenceType       = Traits<TypeParam>::isRef,
      isRvalueReferenceType = Traits<TypeParam>::isRRef,
      isConst               = Traits<TypeParam>::isConst,
      isClass               = sizeof(fun<TypeParam>(0)) == sizeof(Char2),
      isPlainType           = !(isPointerType || isReferenceType || isRvalueReferenceType || isConst || isClass)
   };
};



#endif

