//杨氏矩阵查找

bool searchMatrix(vector<vector int> > &matrix,int target)
{
    
    int m = matrix.size();
    int n = matrix[0].size();
    int r = 0 ;
    int c = n -1;
    for(; (r < m) && (c >= 0);){
        if(matrix[r][c] > target){
            --c;
        }else if(matrix[r][c] < target){
            ++r;
        }else{
            return true;
        }
    }
    return false;
}