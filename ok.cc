  
#include <iostream>
using namespace std;


class Client_Class {
public:
	bool is_alive() { return check; }

private:
	bool check = false;
};

class Target_Class {
public:
	void set_render_frame_host(Client_Class* cc) {
		client_ptr = cc;
	}

	void Access_After_Free() {
		if (!client_ptr->is_alive()) {
			cout << "accessed" << endl;
		}
	}

private:
	Client_Class* client_ptr;
};

void Delete_Obj(Client_Class* rfh) {
	delete rfh;
	cout << "deleted" << endl;
}

int main() {
	Client_Class* render_frame_host = new Client_Class;
	Target_Class* TC = new Target_Class;
	TC->set_render_frame_host(render_frame_host);

	//deletes object pointed to by render_frame_host
	Delete_Obj(render_frame_host);

	//TC outlives render_frame_host and then accesses it
	//without observing its lifetime
	TC->Access_After_Free();
}
