/*
 *  RNtrack - FTN message tracker/router
 *
 *  a_list.hpp - Alternative CONTAINER template library
 *
 *  Copyright (c) 2003-2005 Alex Soukhotine, 2:5030/1157
 *	
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  $Id: a_list.hpp,v 1.1.1.1 2005/01/14 19:17:59 ph0enix Exp $
 */

/*
Copyright (C) Andrey V. Stolyarov <croco@croco.net> 1997,98,99
First compiled with Borland C++ 4.52, Mar 1997
Ported to GNU C++ (g++) / Linux       Feb 1999
*/

#ifndef _A_LIST_HPP_
#define _A_LIST_HPP_


#ifndef NULL
#define NULL 0
#endif

////////////////////////////////////////////////////////////////////////////////
// "List Of Nothing" - the only use of this class is to derive some
// real lists from it.
class TAbstractList {

  public:

    class AbstractElem {
        friend class TAbstractList;
        AbstractElem *Prev, *Next;
//      protected:
      public:
        AbstractElem() { Prev = Next = NULL; }
        virtual ~AbstractElem() {}
        AbstractElem* operator +(int i)
        {
          if (i==0) return this;
          AbstractElem *el = this;
          if (i>0) {
            for (int j = 0; j < i && el; j++, el = el -> Next);
          } else {
            for (int j = 0; j > i && el; j--, el = el -> Prev);
          }
          return el;
        }
        AbstractElem* operator -(int i)
        {
          return operator +(-i);
        }
    };

    private:
        AbstractElem *First, *Last;
    public:

    TAbstractList()
    {
       First = Last = NULL;
    }
    void Clear()
    {
       while(First)
       {
          AbstractElem *p = First;
          UnlinkElem(First);
          delete p;
       }
    }
    void UnlinkElem( AbstractElem *el )
    {
       if ( el->Prev ) {
         el->Prev->Next = el->Next;
       } else {
         First = el->Next;
       }
       if ( el->Next ) {
         el->Next->Prev = el->Prev;
       } else {
         Last = el->Prev;
       }
    }
    void LinkElemToBegin( AbstractElem *el )
    {
       el->Prev = NULL;
       el->Next = First;
       if (First)
         First->Prev = el;
       else
         Last = el;
       First = el;
    }
    void LinkElemToEnd( AbstractElem *el )
    {
       el->Next = NULL;
       el->Prev = Last;
       if (Last)
         Last->Next=el;
       else
         First = el;
       Last = el;
    }
    void LinkElemBefore( AbstractElem *el, AbstractElem *newEl )
    {
       if (!el->Prev) {
         LinkElemToBegin(newEl);
       } else {
         newEl->Prev = el->Prev;
         newEl->Next = el;
         el->Prev->Next = newEl;
         el->Prev = newEl;
       }
    }
    void LinkElemAfter( AbstractElem *el, AbstractElem *newEl )
    {
       if (!el->Next) {
         LinkElemToEnd(newEl);
       } else {
         newEl->Next = el->Next;
         newEl->Prev = el;
         el->Next->Prev = newEl;
         el->Next = newEl;
       }
    }
    int MoveElemForward( AbstractElem *el ) {
       if (!el->Next) {
         return 0;
       } else {
         AbstractElem *el2 = el->Next;
         UnlinkElem(el);
         LinkElemAfter(el2, el);
         return 1;
       }
    }
    int MoveElemBackward( AbstractElem *el ) {
       if (!el->Prev) {
         return 0;
       } else {
         AbstractElem *el2 = el->Prev;
         UnlinkElem(el);
         LinkElemBefore(el2, el);
         return 1;
       }
    }
    void MoveElemToBegin( AbstractElem *el ) {
       UnlinkElem(el);
       LinkElemToBegin(el);
    }
    void MoveElemToEnd( AbstractElem *el ) {
       UnlinkElem(el);
       LinkElemToEnd(el);
    }
    AbstractElem *GetFirst() { return First; }
    AbstractElem *GetLast() { return Last; }
    ~TAbstractList()
    {
       Clear();
    }
};

////////////////////////////////////////////////////////////////////////////////
// Direct list. Useful for classes for which it's no loose to copy them.
// For example, it's very good idea to use this particular template with
// int, long, float, char etc.
// Objects are stored directly in Elements of the list, so actually they are
// copies of objects you passed to the methods of the class. This requires T
// to have a COPY CONSTRUCTOR.
template <class T>
class BiList : protected TAbstractList
{
  public:

    class ElemPtr;

  protected:

    class Elem : public AbstractElem {
        friend class BiList<T>;
	friend class BiList<T>::ElemPtr;
      public:
        T data;
        operator T&() { return data; }
        Elem* operator +(int i) {
          return (Elem*)((*(AbstractElem*)this)+i);
        }
        Elem* operator -(int i) {
          return (Elem*)((*(AbstractElem*)this)-i);
        }
      protected:
        Elem(T &t) : data(t) {}
        virtual ~Elem() {}
    };

    Elem *GetFirstElem() {
       return (Elem*)TAbstractList::GetFirst();
    }
    Elem *GetLastElem() {
       return (Elem*)TAbstractList::GetLast();
    }

  public:

    class ElemPtr {
	friend class BiList<T>;
        Elem *p;
        ElemPtr(Elem *e) { p = e; }
      protected:
        Elem* GetP() { return p; }
      public:
        ElemPtr() { p = NULL; }
        ElemPtr(const ElemPtr &e2) { p = e2.p; }
        ~ElemPtr() {}

        ElemPtr  operator ++()            // Preincrement
               { p = p ? (*p)+1 : 0; return *this; }
        ElemPtr  operator --()            // Predecrement
               { p = p ? (*p)-1 : 0; return *this; }
        ElemPtr  operator ++(int)         // Postincrement
               { Elem *p2 = p; p = p ? (*p)+1 : 0; return ElemPtr(p2); }
        ElemPtr  operator --(int)         // Postdecrement
               { Elem *p2 = p; p = p ? (*p)-1 : 0; return ElemPtr(p2); }
        ElemPtr  operator +(int i) { return ElemPtr((*p)+i); }
        ElemPtr  operator -(int i) { return ElemPtr((*p)-i); }
        operator T* () { return p ? &(p->data) : NULL; }
    };


  public:

    BiList() : TAbstractList() {}
    ~BiList() { Clear(); }
    ElemPtr AddToBegin( T &t ) {
              Elem *el = new Elem(t);
              LinkElemToBegin(el);
              return ElemPtr(el);
            }
    ElemPtr AddToEnd( T &t ){
              Elem *el = new Elem(t);
              LinkElemToEnd(el);
              return ElemPtr(el);
            }
    ElemPtr InsertBefore( ElemPtr &elp, T &t) {
              Elem *el = elp.GetP();
              Elem *nel = new Elem(t);
              LinkElemBefore(el, nel);
              return ElemPtr(nel);
            }
    ElemPtr InsertAfter( ElemPtr &elp, T &t){
              Elem *el = elp.GetP();
              Elem *nel = new Elem(t);
              LinkElemAfter(el,nel);
              return ElemPtr(nel);
            }
    ElemPtr GetFirst() {
            return ElemPtr(GetFirstElem());
         }
    ElemPtr GetLast() {
            return ElemPtr(GetLastElem());
         }
    void Remove( ElemPtr &elp ) {
           Elem *el = elp.GetP();
           UnlinkElem(el);
           delete el;
         }
    void PlaceToBegin( ElemPtr &elp ) {
           Elem *el = elp.GetP();
           MoveElemToBegin(el);
         }
    void PlaceToEnd( ElemPtr &elp ) {
           Elem *el = elp.GetP();
           MoveElemToEnd(el);
         }
    void Clear() {
           TAbstractList::Clear();
         }
    int IsEmpty() { return GetFirstElem() == NULL; }
    int ElemCount() {
           int c = 0;
           ElemPtr p(GetFirstElem());
           while (p) { c++; p++; }
           return c;
         }
};


#define BILIST_FOREACH(bclass,list,itname)\
   for (BiList<bclass>::ElemPtr itname = list->GetFirst(); itname; itname++)


////////////////////////////////////////////////////////////////////////////////
// This template assumes that T is a (small?) structure or class or unit.
// The only difference from previous class is that there is operator->()
// for ElemPtr which makes it more like a real pointer to an object of T
template <class T>
class StrBiList : public BiList<T> {
  public:
  class ElemPtr : public BiList<T>::ElemPtr {
    public:
    ElemPtr(typename BiList<T>::ElemPtr &e) : BiList<T>::ElemPtr(e){}
    operator T*();
    T* operator->() { return operator T*(); }
  };
  ElemPtr AddToBegin( T &t ) {
             return (ElemPtr)BiList<T>::AddToBegin(t);
          }
  ElemPtr AddToEnd( T &t ) {
             return (ElemPtr)BiList<T>::AddToEnd(t);
          }
  ElemPtr InsertBefore( ElemPtr &elp, T &t) {
             return (ElemPtr)BiList<T>::InsertBefore(elp,t);
          }
  ElemPtr InsertAfter( ElemPtr &elp, T &t) {
             return (ElemPtr)BiList<T>::InsertAfter(elp,t);
          }
  ElemPtr GetFirst() {
             return (ElemPtr)BiList<T>::GetFirst();
          }
  ElemPtr GetLast() {
             return (ElemPtr)BiList<T>::GetLast();
          }


};

#define STRBILIST_FOREACH(bclass,list,itname)\
   for (StrBiList<bclass>::ElemPtr itname = list->GetFirst(); itname; itname++)

////////////////////////////////////////////////////////////////////////////////
// This class is "Indirect" double-linked list. We assume that it's elements
// are classes or structures (please no arrays ;-) to define operator->() to
// access them.

template <class T>
class IndBiList : protected TAbstractList
{
  public:

    class ElemPtr;

  protected:

    class Elem : public AbstractElem {
        friend class IndBiList<T>;
        friend class ElemPtr;
        char Owner;
      public:
        T *data;
        operator T*() { return data; }
        Elem* operator +(int i) {
          return (Elem*)((*(AbstractElem*)this)+i);
        }
        Elem* operator -(int i) {
          return (Elem*)((*(AbstractElem*)this)-i);
        }
      protected:
        Elem(T *t, char own = 1) { data = t; Owner = own; }
        virtual ~Elem() { if (Owner) delete data; }
    };

    Elem *GetFirstElem() {
       return (Elem*)TAbstractList::GetFirst();
    }
    Elem *GetLastElem() {
       return (Elem*)TAbstractList::GetLast();
    }

  public:

    class ElemPtr {
        friend class IndBiList<T>;
        Elem *p;
        ElemPtr(Elem *e) { p = e; }
      protected:
        Elem* GetP() { return p; }
      public:
        ElemPtr() { p = NULL; }
        ElemPtr(const ElemPtr &e2) { p = e2.p; }
        ~ElemPtr() {}

        ElemPtr  operator ++()            // Preincrement
               { p = p ? (*p)+1 : 0; return *this; }
        ElemPtr  operator --()            // Predecrement
               { p = p ? (*p)-1 : 0; return *this; }
        ElemPtr  operator ++(int)         // Postincrement
               { Elem *p2 = p; p = p ? (*p)+1 : 0; return ElemPtr(p2); }
        ElemPtr  operator --(int)         // Postdecrement
               { Elem *p2 = p; p = p ? (*p)-1 : 0; return ElemPtr(p2); }
        ElemPtr  operator +(int i) { return ElemPtr((*p)+i); }
        ElemPtr  operator -(int i) { return ElemPtr((*p)-i); }
	T* operator -> () const { return p ? (T*) p->data : (T*) NULL; }
	operator T* () const { return operator ->(); }
//        operator T* () const { return p ? (T*) p->data : (T*) NULL; }
//        T* operator -> () const { return (operator T*()); }
    };


  public:

    IndBiList() : TAbstractList() {}
    ~IndBiList() { Clear(); }
    ElemPtr AddToBegin( T *t, char own=1 ) {
              Elem *el = new Elem(t,own);
              LinkElemToBegin(el);
              return ElemPtr(el);
            }
    ElemPtr AddToEnd( T *t, char own=1 ){
              Elem *el = new Elem(t,own);
              LinkElemToEnd(el);
              return ElemPtr(el);
            }
    ElemPtr InsertBefore( ElemPtr &elp, T *t, char own=1 ) {
              Elem *el = elp.GetP();
              Elem *nel = new Elem(t,own);
              LinkElemBefore(el, nel);
              return ElemPtr(nel);
            }
    ElemPtr InsertAfter( ElemPtr &elp, T *t, char own=1 ){
              Elem *el = elp.GetP();
              Elem *nel = new Elem(t,own);
              LinkElemAfter(el,nel);
              return ElemPtr(nel);
            }
    ElemPtr AddToBegin( T &t ) {
              return AddToBegin(&t,0);
            }
    ElemPtr AddToEnd( T &t ) {
              return AddToEnd(&t,0);
            }
    ElemPtr InsertBefore( ElemPtr &elp, T &t ) {
              return InsertBefore(elp, &t, 0);
            }
    ElemPtr InsertAfter( ElemPtr &elp, T &t ) {
              return InsertAfter(elp, &t, 0);
            }
    ElemPtr GetFirst() {
            return ElemPtr(GetFirstElem());
         }
    ElemPtr GetLast() {
            return ElemPtr(GetLastElem());
         }
    void Remove( ElemPtr &elp ) {
           Elem *el = elp.GetP();
           UnlinkElem(el);
           delete el;
         }
    void PlaceToBegin( ElemPtr &elp ) {
           Elem *el = elp.GetP();
           MoveElemToBegin(el);
         }
    void PlaceToEnd( ElemPtr &elp ) {
           Elem *el = elp.GetP();
           MoveElemToEnd(el);
         }
    void Clear() {
           TAbstractList::Clear();
         }
    int IsEmpty() { return GetFirstElem() == NULL; }
    int ElemCount() {
           int c = 0;
           ElemPtr p(GetFirstElem());
           while (p) { c++; p++; }
           return c;
         }
};


#define INDBILIST_FOREACH(bclass,list,itname)\
   for (IndBiList<bclass>::ElemPtr itname = list.GetFirst(); itname; itname++)


#endif // sentry
