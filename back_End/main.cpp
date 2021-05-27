#include "dijsktra_on_VEB.cpp"

int main(){
    int source,destination;
    cout<<"Enter Source Node: "<<endl;
    cin>>source;
    destination=dijsktra_on_VEB(source);
    cout << "\nNearest Destination from Source: "<<source<<" is : "<<destination<<endl; //prints the output
}