public int[] pre(String pattern){
        int pre[]=new int[pattern.length()];
        int l=0,r=1;
        while(r<pattern.length()){
            if(pattern.charAt(r)==pattern.charAt(l)){
                pre[r]=l+1;
                l++;
                r++;
            }else{
                if(l==0)r++;
                else{
                    l=pre[l-1];
                }
            }
        }
        return pre;
    }
