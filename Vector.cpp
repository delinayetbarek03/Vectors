#include "vector.hpp"



size_t my::vector::size()     const { return siz; }
size_t my::vector::capacity() const { return cap; }

bool my::vector::empty() const { return siz == 0; }






my::vector::vector() : siz(0), cap(0), ptr(nullptr) {}


my::vector::~vector() {
    delete[] ptr;
}



// v[3] no assignments can be made, accessor

const int& my::vector::operator[](size_t n) const {
    return ptr[n]; // is this the same as *(ptr + n)
}


// v[1] = 5; modifier
int& my::vector::operator[](size_t n){
    return ptr[n];
}




my::vector::vector(size_t sz) : siz(sz), cap(sz), ptr(new int [sz]() ) {}

my::vector::vector(size_t sz, int nums) : siz(sz), cap(sz), ptr(new int [sz]) {
    for( size_t i = 0; i < sz; ++i ){
        ptr[i] = nums;
    }
}


my::vector::vector(std::initializer_list<int> il) : siz( il.size() ), cap( il.size() ), ptr(new int [il.size()] ) {
    size_t x = 0;
    for( int val : il ){
        ptr[x] = val;
        ++x;
    }
}




void my::vector::clear() {
    siz = 0;
}



void my::vector::reserve(size_t n) {
    if( n > cap ) {
        new_capacity(n);
    }
}


void my::vector::push_back(int x) {
    if( cap == 0 ) {
        reserve(1);
        ++siz;
        ptr[siz-1] = x;

        } else if ( siz == cap){
            reserve(2*cap);
            ++siz;
            ptr[siz-1] = x; // *( ptr + (siz-1) ) = x
            } else {
                ++siz;
                ptr[siz-1] = x;
                }
}


void my::vector::resize(size_t n , int i) {
    if( n <= siz ) {
        siz = n;
    }

    if( n > siz ) {
        if( n <= cap ) {
            size_t old_siz = siz;
            siz = n;
            for( size_t indx = old_siz; indx < n; ++indx ){
                ptr[indx] = i;
            }
        }

        else if( n > cap ) {
            
            if( n <= (2*cap) ) {
                reserve(2*cap);
                size_t old_siz = siz;
                siz = n;
                for( size_t indx = old_siz; indx < n; ++indx ){
                    ptr[indx] = i;
                }
                }
                
            if( n > (2*cap) ) {
                reserve(n);
                size_t old_siz = siz;
                siz = n;
                for( size_t indx = old_siz; indx < n; ++indx ){
                    ptr[indx] = i;
                }
            }
        }
        
        
    }
}




// swap
void my::vector::swap(vector& v) {
    std::swap( siz, v.siz );
    std::swap( ptr, v.ptr );
    std::swap( cap, v.cap );
}

// move constructor
my::vector::vector(vector&& other) : vector() {
    
    swap(other);
}



// move assignment
my::vector& my::vector::operator=(vector&& other) {
    
    swap(other);
    
    return *this; }


// copy constructor
my::vector::vector(const vector& v) : siz( v.siz ), cap( v.cap ), ptr( new int [v.siz] ) {
    if( siz < cap ) {
        cap = siz;
    }
    for( size_t i = 0; i < siz; ++i ) {
        ptr[i] = v.ptr[i];
    }
}

// copy assignment operator
// COPY AND SWAP

my::vector& my::vector::operator=(const vector& other) {
    
    if( this == &other) { return *this; }
    
    my::vector copy(other);
    
    swap(copy);

    return *this;
    
    }




void my::vector::pop_back() { siz -= 1; }



void my::vector::new_capacity(size_t n) {
    cap = n;
    int* new_ptr = new int[cap];
    
    for (size_t i = 0; i < siz; ++i) {
        new_ptr[i] = ptr[i];
    }
    delete[] ptr;

    ptr = new_ptr;
}




const int* my::vector::data() const { return ptr; }
      int* my::vector::data()       { return ptr; }


void my::swap(vector& v1, vector& v2) {
    v1.swap(v2);
}
