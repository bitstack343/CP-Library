//range addition and query with point updates
struct Lazy{
    vector<ll> segt,lazy;
    ll n;
    Lazy(ll n){
        this->n=n;
        segt.resize(4*n,INF_ADD);
        lazy.resize(4*n,0);
    }
    ll merge(ll l,ll r){
        return min(l,r);
    }
    void push(ll v){
        segt[2*v]+=lazy[v];
        segt[2*v+1]+=lazy[v];
        lazy[2*v]+=lazy[v];
        lazy[2*v+1]+=lazy[v];
        lazy[v]=0;
    }
    void set_upd(ll pos,ll val){
        set_upd(1,1,n,pos,val);
    }
    void set_upd(ll v,ll l,ll r,ll pos,ll val){
        if(l==r){
            segt[v]=val;
        }
        else{
            push(v);
            ll m=(l+r)/2;
            if(pos<=m){
                set_upd(2*v,l,m,pos,val);
            }
            else{
                set_upd(2*v+1,m+1,r,pos,val);
            }
            segt[v]=merge(segt[2*v],segt[2*v+1]);
        }
    }
    void add_upd(ll l,ll r,ll delta){
        add_upd(1,1,n,l,r,delta);
    }
    void add_upd(ll v,ll tl,ll tr,ll l,ll r,ll delta){
        if(l>r){
            return;
        }
        if((tl==l) and (tr==r)){
            segt[v]+=delta;
            lazy[v]+=delta;
        }
        else{
            push(v);
            ll tm=(tl+tr)/2;
            add_upd(2*v,tl,tm,l,min(r,tm),delta);
            add_upd(2*v+1,tm+1,tr,max(l,tm+1),r,delta);
            segt[v]=merge(segt[2*v],segt[2*v+1]);
        }
    }
    ll query(ll l,ll r){
        return query(1,1,n,l,r);
    }
    ll query(ll v,ll l,ll r,ll ql,ll qr){
        if(ql>qr){
            return INF_ADD;
        }
        if((l==ql) and (r==qr)){
            return segt[v];
        }
        push(v);
        ll m=(l+r)/2;
        return merge(query(2*v,l,m,ql,min(m,qr)),query(2*v+1,m+1,r,max(m+1,ql),qr));
    }
};
