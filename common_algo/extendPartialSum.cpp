//
// Created by luoxiYun on 2021/4/8.
//
#include "common.h"

class partialSumVariant{

    vector<vector<int>> matrixPartialSum;
public:
    void setMatrixPartialSum( vector<vector<int>> &matrix ){
        int row = matrix.size(), col = matrix[0].size();
        matrixPartialSum = vector<vector<int>>( row , vector<int>(col, 0) );
        matrixPartialSum[0][0] = matrix[0][0];
        for( int j = 1; j < col; j++ )
            matrixPartialSum[0][j] =matrixPartialSum[0][j-1] + matrix[0][j];
        for( int i = 1; i < row; i++ )
            matrixPartialSum[i][0] =matrixPartialSum[i-1][0] + matrix[i][0];
        for( int i = 1; i < row; i++ ){
            for( int j = 1; j < col; j++ )
                matrixPartialSum[i][j] =(matrixPartialSum[i-1][j] + matrixPartialSum[i][j-1] -
                                            matrixPartialSum[i-1][j-1] + matrix[i][j]);
        }
    }

    //test matrix partial sum correct
    void getMatrixPartialSum(){
        for( int i = 0; i < matrixPartialSum.size(); i++){
            for (int j = 0; j < matrixPartialSum[i].size(); ++j) {
                cout<<matrixPartialSum[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    //O(n^4)复杂度
    int calcuMaximumSubMatrixSum( vector<vector<int>> &matrix ){
        int result = matrix[0][0];
        int row = matrix.size(), col = matrix[0].size();
        setMatrixPartialSum(matrix);
        for( int begin_row = 0; begin_row < row; begin_row++ ){
            for( int end_row = begin_row ; end_row < row; end_row++ ){
                for( int begin_col = 0; begin_col < col; begin_col++ ){
                    for( int end_col = begin_col; end_col < col; end_col++ ){
                        result = max( result,  matrixBlockSum(begin_row, begin_col, end_row, end_col));
                    }
                }
            }
        }
        return result;
    }

    int matrixBlockSum( int upper_row, int upper_col, int lower_row, int lower_col ){
        if( upper_row == 0 && upper_col == 0 )
            return matrixPartialSum[lower_row][lower_col];
        else if( upper_col == 0 )
            return matrixPartialSum[lower_row][lower_col] - matrixPartialSum[upper_row-1][lower_col];
        else if( upper_row == 0 )
            return matrixPartialSum[lower_row][lower_col] -  matrixPartialSum[lower_row][upper_col-1];
        return matrixPartialSum[lower_row][lower_col] - matrixPartialSum[upper_row-1][lower_col]
                - matrixPartialSum[lower_row][upper_col-1] + matrixPartialSum[upper_row-1][upper_col-1];
    }
    //优化
    int optMaximumSubMatrixSum( vector<vector<int>> &matrix ){
        int result = matrix[0][0];
        //int upper_row, upper_col, lower_row, lower_col;
        int row = matrix.size(), col = matrix[0].size();
        int upperRow, leftCol, lowerRow, rightCol;
        setMatrixPartialSum(matrix);
        for( int i = 0; i < row; i++ ){
            for( int j = i; j < row; j++ ){
                int start = matrixBlockSum( i, col-1, j, col-1);
                int all = start;
                int lc = col - 1, rc = col - 1;
                int tmpLeftCol = col - 1, tmpRightCol = col - 1;

                //cout<<"begin row: "<<i<<"end row: "<<j<<endl;
                //cout<<"["<<col-1<<"]: "<<start<<endl;
                for( int k = col-2; k >= 0; k-- ){
                    int current = matrixBlockSum( i, k, j, k );
                    if( current + start <= current ) {
                        tmpLeftCol = k;
                        tmpRightCol = k;
                    }else
                        tmpLeftCol = k;
                    start = max(current , current+start);
                    if( all < start ){
                        all = start;
                        lc = tmpLeftCol;
                        rc = tmpRightCol;
                    }
                    //all = max( all, start );
                    /*if( result < start ){
                        result = start;
                    }*/
                }
                if( result <= all ){
                    upperRow = i; lowerRow = j;
                    leftCol = lc; rightCol = rc;
                    result = all;
                }

                //result = max(result, all);
            }
        }
        return result;
    }
};

int main(){

    /*srand(time(NULL));
    for(int i = 0; i < 100; i++) {

        int row = rand() % 100 + 1, col = rand() % 100 + 1;
        //cout << row << " " << col << endl;
        vector<vector<int>> matrix(row, vector<int>(col, 0));
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                matrix[i][j] = rand() % 100 - 50;
                //cout << matrix[i][j] << " ";
            }
            //cout << endl;
        }*/
        //cout << endl;

        vector<vector<int>>
            matrix = {
                {-4228, -3710, -1116, -707, 3656, 1900, 2619, 4462},
                {1852, 1402, 2703, -3542, 1604, -3016, 939, -4155},
                {-4686, -3894, 2267, 4283, -4856, 37, 190, 681},
                {3839, 3510, 3156, -3545, -61, -2380, 2041, -1784},
                {-3161, -3560, -4817, -2385, -2835, -4179, -2657, -4519},
                {95, 824, -4741, -2070, 3194, -4135, -1052, 4488},
                {45, 4651, -4565, -2563, 3094, 1621, 2079, 699},
                {3844, -2491, -1337, -4562, 3560, 4912, -361, 494},
                {1193, 341, -4272, -2619, 3735, 2870, -338, -2936},
                {-3134, 158, 1216, -816, 3430, 3938, -2991, -3371}
        };
        partialSumVariant psv;
        psv.setMatrixPartialSum(matrix);
        //psv.getMatrixPartialSum();
        cout << psv.calcuMaximumSubMatrixSum(matrix) << endl;
        cout << psv.optMaximumSubMatrixSum(matrix) << endl;
        if (psv.calcuMaximumSubMatrixSum(matrix) != psv.optMaximumSubMatrixSum(matrix))
            cout << "==============ooops================" << endl;


    return 0;
}