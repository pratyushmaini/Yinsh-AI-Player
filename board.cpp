class Board{
	//position to what is contained in it -- pos = tuple of x, y where min y starts at bottom most node

	

	Hex convertToHex(int x, int y){
		int r = y;
		int p = 0;

		//Write Code here to convert
		Hex output(r,p);
		return output;

	}

	Cart convertToCart(int r, int p){
		int x = 0;
		int y = r;

		//Write Code here to convert
		Cart output(x,y);
		return output;

	}

	//final output -- M r p -- where M = move type, r = Ring no., p = position in ring starting from 0 


}

class Hex{
	int ring;
	int pos;
	public:
	Hex(int r, int p){
		ring = r;
		pos = p;
	}
}

class Cart{
	int x;
	int y;
	public:
	Cart (int a,int b){
		x = a;
		y = b;
	}
}