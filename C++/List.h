template <typename T>
//template class so that the list ADT can hold any data type
class List{
    public:
        //standard functions for the list ADT
        virtual void insertFront(T data)=0;
        virtual void insertBack(T data)=0;
        virtual T removeFront()=0;
        virtual T removeBack()=0;
        virtual T getFront()=0;
        virtual T remove(T key)=0;
        virtual bool contains(T value)=0;
        virtual bool isEmpty()=0;
        virtual unsigned int getSize()=0;
};