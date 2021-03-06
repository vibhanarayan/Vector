// Implementation of the templated Vector class
// ECE4893/8893 lab 3
// YOUR NAME HERE

#include <iostream> // debugging
#include "Vector.h"

// Your implementation here
// Fill in all the necessary functions below
using namespace std;

// Default constructor
template <typename T>
Vector<T>::Vector()
{
elements=NULL;
count=0;
reserved=0;
}

// Copy constructor
template <typename T>
Vector<T>::Vector(const Vector& rhs)
{
count=rhs.count;
reserved=rhs.reserved;
elements=(T*) malloc(sizeof(T));
for(int i=0; i<count; i++){
new(&elements[i]) T(rhs.elements[i]);

}
}

// Assignment operator
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& rhs)
{
if(this==rhs){
return *this;
}
if (elements!=NULL){
	for(int i=0;i<count;i++){
	elements[i].~T();
	}	
free(elements);
}
count=rhs.count;
reserved= rhs.reserved;
elements =(T*)malloc(reserved*sizeof(T));
for (int i =0; i<count; i++){
new(&elements[i]) T (rhs.elements[i]);
}
}
#ifdef GRAD_STUDENT
// Other constructors
template <typename T>
Vector<T>::Vector(size_t nReserved)
{ // Initialize with reserved memory
count = 0;
  reserved = nReserved;
  elements = (T*) malloc(nReserved*sizeof(T));
}

template <typename T>
Vector<T>::Vector(size_t n, const T& t)
{ // Initialize with "n" copies of "t"
count = n;
  elements = (T*) malloc(n*sizeof(T));
  for (int i = 0; i < count; i++)
    {
      new (&elements[i]) T(t);
    }
}


template <typename T>
void Vector<T>::Reserve(size_t n)
{ // Reserve extra memory
this->reserved = n;
elements = (T*) malloc(reserved*sizeof(T));
}

#endif

// Destructor
template <typename T>
Vector<T>::~Vector()
{

if(elements){
	for(int i=0; i<count; i++){
		elements[i].~T();
}
free(elements);
}
count=0;
reserved=0;
}
// Add and access front and back
template <typename T>
void Vector<T>::Push_Back(const T& rhs)
{
if (count == reserved){
	count++; reserved++;
 	T* t = (T*) malloc(reserved*sizeof(T));
	 for (int i = 0; i < count - 1; i++){
		new (&t[i]) T(elements[i]);
		elements[i].~T();
}

	free(elements);
	new(&t[count-1]) T(rhs);
	elements=t;
}

else{
	count++;
	new (&elements[count-1]) T(rhs);
}
}

template <typename T>
void Vector<T>::Push_Front(const T& rhs)
{
if (count == reserved)
    {
      count++;
      reserved++;
      T* t = (T*) malloc(reserved*sizeof(T));
      for (int i = 1; i < count; i++)
	{
	  new (&t[i]) T(elements[i-1]); 
          elements[i-1].~T();}

	free(elements);
new (t) T(rhs);
elements=t;}

else
    {
      for (int i = count; i > 1; i--)
	{
	  new (&elements[i]) T(elements[i-1]);
	  elements[i-1].~T();
	}
      new (elements) T(rhs);
      count++;
    }
}

template <typename T>
void Vector<T>::Pop_Back()
{ // Remove last element
if(count>0){
	count--;
	elements[count].~T();
}
}


template <typename T>
void Vector<T>::Pop_Front()
{ // Remove first element
if (count > 0)
    {
      elements[0].~T(); 
        for (int i = 0; i < count - 1; i++)
            	{new (&elements[i]) T(elements[i+1]);
                   elements[i+1].~T();
            	}
             count--;
         } 
}

// Element Access
template <typename T>
T& Vector<T>::Front() const
{
return elements[0];
}

// Element Access
template <typename T>
T& Vector<T>::Back() const
{
return elements[count-1];
}

template <typename T>
const T& Vector<T>::operator[](size_t i) const
{ // const element access
return elements[i];
}

template <typename T>
T& Vector<T>::operator[](size_t i)
{//nonconst element access
return elements[i];
}

template <typename T>
size_t Vector<T>::Size() const
{
return count;
}

template <typename T>
bool Vector<T>::Empty() const
{
return(count==0);
}

// Implement clear
template <typename T>
void Vector<T>::Clear()
{for (int i = 0; i < count; i++)
    {
      elements[i].~T();
    }
  count = 0;
}

// Iterator access functions
template <typename T>
VectorIterator<T> Vector<T>::Begin() const
{
  return VectorIterator<T>(elements);
}

template <typename T>
VectorIterator<T> Vector<T>::End() const
{
return VectorIterator<T>(elements+count);
}

#ifdef GRAD_STUDENT
// Erase and insert
template <typename T>
void Vector<T>::Erase(const VectorIterator<T>& it)
{
 count--;
  VectorIterator<T> t;
  int position = 0;  

     for (t = elements; t!= elements + count - 1; t++)
         {
               position++; 
               if(t==it)
                 break;
            }
          elements[position-1].~T(); 
                     	        
      for (int i = position - 1; i < count; i++)
      {
           new (&elements[i]) T(elements[i+1]);
           elements[i+1].~T();
       }
}

template <typename T>
void Vector<T>::Insert(const T& rhs, const VectorIterator<T>& it)
{
count++;
  T* t = (T*) malloc(count*sizeof(T)); 
  VectorIterator<T> tt;
  int position = 0;
 
     for(tt = elements; tt != elements + count - 1; tt++)
         {
               position++;
                     if(tt==it)
                     	break;
                     	    }
                     	      
        for(int i = 0; i < position - 1; i++)
            {
              new (&t[i]) T(elements[i]);
              elements[i].~T();
             }
        new (&t[position-1]) T(rhs); 
  
         for(int i = position; i < count; i++)     {
              new (&t[i]) T(elements[i-1]);
              elements[i-1].~T();   }
                   	                                                        free(elements);
   elements = t;

}
#endif

// Implement the iterators

// Constructors
template <typename T>
VectorIterator<T>::VectorIterator()
{
current = NULL;
}

template <typename T>
VectorIterator<T>::VectorIterator(T* c)
{
current=c;
}

// Copy constructor
template <typename T>
VectorIterator<T>::VectorIterator(const VectorIterator<T>& rhs)
{
current=rhs.current;
}

// Iterator defeferencing operator
template <typename T>
T& VectorIterator<T>::operator*() const
{
return *current;
}

// Prefix increment
template <typename T>
VectorIterator<T>  VectorIterator<T>::operator++()
{  current++;
  return *this;
}


// Postfix increment
template <typename T>
VectorIterator<T> VectorIterator<T>::operator++(int)
{
  VectorIterator<T> t(current);
  current++;
  return t;

}

// Comparison operators
template <typename T>
bool VectorIterator<T>::operator !=(const VectorIterator<T>& rhs) const
{
return (current != rhs.current);
}

template <typename T>
bool VectorIterator<T>::operator ==(const VectorIterator<T>& rhs) const
{
return (current == rhs.current);
}


