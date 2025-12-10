class sgtree{
    vector<int>seg;
    public:
    sgtree(int n){
        seg.resize(4*n+1);
    }

    void buildsgt(int ind, int low, int high, vector<int>&nums){
        if(low==high){
            seg[ind]=nums[low];
            return;
        }

        int mid=(low+high)/2;
        buildsgt(2*ind+1, low, mid, nums);
        buildsgt(2*ind+2, mid+1, high, nums);
        seg[ind]=seg[2*ind+1]+seg[2*ind+2];
    }

    void update(int ind, int low, int high, int &i, int &val){
        if(low==high){
            seg[ind]=val;
            return;
        }
        int mid=(low+high)/2;
        if(i<=mid) update(2*ind+1, low, mid, i, val);
        else update(2*ind+2, mid+1, high, i, val);
        seg[ind]=seg[2*ind+1]+seg[2*ind+2];
    }

    int query(int ind, int low, int high, int &l, int &r, vector<int>&nums){
        if(low>r || high<l) return 0;
        if(low>=l && high<=r) return seg[ind];
        int mid = (low + high)/2;
        int left = query(2*ind+1, low, mid, l, r, nums);
        int right = query(2*ind+2, mid+1, high, l, r, nums);
        return left+right;
    }
};
