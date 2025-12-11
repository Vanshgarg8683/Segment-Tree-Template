class sgtree{
    public:
    vector<int>seg,lazy;
    sgtree(int n){
        seg.resize(4*n+1,0);
        lazy.resize(4*n+1,0);
    }
    // Build sgt
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
    // point update
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
    // Range Update(Lazy Propagation)
    void update(int ind, int low, int high, int &l, int &r, int &val){
        seg[ind] = seg[ind] + (high-low+1)*lazy[ind];
        if(low!=high){
            lazy[2*ind+1] += lazy[ind];
            lazy[2*ind+2] += lazy[ind];
        }
        lazy[ind]=0;
        
        if(high<l || low>r) return;
        
        if(low>=l && high<=r){
            seg[ind]+=(high-low+1)*val;
            if(low!=high){
                lazy[2*ind+1]+=val;
                lazy[2*ind+2]+=val;
            }
            return;
        }
        
        int mid=(low+high)/2;
        update(2*ind+1, low, mid, l, r, val);
        update(2*ind+2, mid+1, high, l, r, val);
        seg[ind]=seg[2*ind+1]+seg[2*ind+2];
    }

    // Query sum
    int query(int ind, int low, int high, int &l, int &r, vector<int>&nums){
        seg[ind] = seg[ind] + (high-low+1)*lazy[ind];
        if(low!=high){
            lazy[2*ind+1] += lazy[ind];
            lazy[2*ind+2] += lazy[ind];
        }
        lazy[ind]=0;
        if(low>r || high<l) return 0;
        if(low>=l && high<=r) return seg[ind];
        int mid = (low + high)/2;
        int left = query(2*ind+1, low, mid, l, r, nums);
        int right = query(2*ind+2, mid+1, high, l, r, nums);
        return left+right;
    }
};
