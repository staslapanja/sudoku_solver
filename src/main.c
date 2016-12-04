#include <stdio.h>
#include <stdlib.h>

//#define DEBUG_PRINT

int display_matrix (int disp_status, int matrix[9][9][9])
/*  Display the sudoku field
    in a 9x9 matrix*/
{
    int x=0;
    int y=0;
    int z=0;
    int count_0=0;
    int count_1=0;
    int count_2=0;
    int count_3=0;
    int count=0;
    int pos;

    for ( y = 0; y < 9; ++y )
    {
        printf("\n");
        for ( x = 0; x < 9; ++x )
        {
            count=0;
            for ( z = 0; z < 9; ++z )
            {
                if (matrix[x][y][z]==0)
                {
                    count_0++;
                }
                if (matrix[x][y][z]==1)
                {
                    count_1++;
                }
                if (matrix[x][y][z]==2)
                {
                    count_2++;
                }
                if (matrix[x][y][z]==3)
                {
                    count++;
                    count_3++;
                    pos = z+1;
                }
            }
            if (count==1)
                printf(" %d",pos);
            else if (count==0)
                printf(" _");
        }
        printf(" \n");
    }
    if (disp_status == 1){
        printf("\n");
        printf("Matrix status:\n");
        printf("  Not       :%d\n",count_0);
        printf("  Possible  :%d\n",count_1);
        printf("  Evaluation:%d\n",count_2);
        printf("  Final     :%d\n",count_3);
    }
    return 0;
}

int finished_correct_matrix (int out_field[9][9][9])
/*  Fill the sudoku matrix with default
    values in correct pattern */
{
    int x=0;
    int y=0;
    int z=0;
    int value=0;
    int offset=0;
    /* populate the field */
    for ( y = 0; y < 9; ++y )
    {
        for ( x = 0; x < 9; ++x )
        {
            value = x+1+offset;
            if ( value > 9 ) {
                value=value-9;
            }
            for ( z = 0; z < 9; ++z )
            {
                if (z == value-1)
                    out_field[x][y][z]=3;
                else
                    out_field[x][y][z]=0;
            }
        }
        offset = offset + 3;
        if (y==2) offset = 1;
        if (y==5) offset = 2;
    }
    return 0;
}

int unfinished_solvable_matrix (int out_field[9][9][9])
/*  Fill the sudoku matrix with an easy challenge */
{
    int x=0;
    int y=0;
    int z=0;
    int pos=0;
    /* solvable sudoku */
    /* base is defined as [y][x] because this way
       the initial values can be human readable */
    int base[9][9]={{0,0,8,0,5,0,0,4,0},
                    {0,0,7,0,3,0,2,6,9},
                    {3,9,0,0,6,0,8,0,0},
                    {0,0,0,0,2,3,5,0,0},
                    {9,0,0,0,1,0,0,0,7},
                    {0,0,1,7,9,0,0,0,0},
                    {0,0,6,0,7,0,0,8,4},
                    {4,2,5,0,8,0,1,0,0},
                    {0,8,0,0,4,0,3,0,0}};

    /* populate the field */
    for ( y = 0; y < 9; ++y )
    {
        for ( x = 0; x < 9; ++x )
        {
            if (base[y][x]==0)
                for ( z = 0; z < 9; ++z )
                    out_field[x][y][z]=1;
            else
            {
                for ( z = 0; z < 9; ++z )
                {
                    out_field[x][y][z]=0;
                }
                pos=base[y][x]-1;
                out_field[x][y][pos]=3;
            }
        }
    }
    return 0;
}

int set_const_matrix (int value, int out_field[9][9][9])
/*  Fill the matrix with default
    value */
{
    int x=0;
    int y=0;
    int z=0;
    /* populate the field */
    for ( x = 0; x < 9; ++x )
    {
        for ( y = 0; y < 9; ++y )
        {
            for ( z = 0; z < 9; ++z )
            {
                out_field[x][y][z]=value;
            }
        }
    }
    return 0;
}

int check_row (int row_num, int matrix[9][9][9])
/*  check if any number duplicates in a row */
{
    int x=0;
    int z=0;
    int error=0;
    int status=0;
    int check[9];
    /*  init the check vector   */
    for ( x = 0; x < 9; ++x ){
        check[x]=0;
    }
    /*  check each element of the row and if
        it has the status 2 or 3 tick the check vector
        for this number. If the same number is found again
        break from the loop and output an error */
    for ( x = 0; x < 9; ++x ){
        for ( z = 0; z < 9; ++z ){
            /*  get status of the element, use -1 because indexes are 0-8   */
            status=matrix[x][row_num-1][z];
            /*  if status is evaluating(2) or final(3) check    */
            if (status > 1){
                if (check[z]==1){
                    error=1;
                    break;
                }
                else {
                    check[z]=1;
                }
            }
        }
        if (error == 1){
            break;
        }
    }
#ifdef DEBUG_PRINT
    printf("Error in row %d: %d\n",row_num,error);
    printf("Check:");
    for ( x = 0; x < 9; ++x ){
            printf(" %d",check[x]);
    }
    printf("\n");
#endif
    return error;

}

int check_column (int column_num, int matrix[9][9][9])
/*  check if any number duplicates in a column */
{
    int y=0;
    int z=0;
    int error=0;
    int status=0;
    int check[9];
    /*  init the check vector   */
    for ( y = 0; y < 9; ++y ){
        check[y]=0;
    }
    /*  check each element of the column and if
        it has the status 2 or 3 tick the check vector
        for this number. If the same number is found again
        break from the loop and output an error */
    for ( y = 0; y < 9; ++y ){
        for ( z = 0; z < 9; ++z ){
            /*  get status of the element, use -1 because indexes are 0-8   */
            status=matrix[column_num-1][y][z];
            /*  if status is evaluating(2) or final(3) check    */
            if (status > 1){
                if (check[z]==1){
                    error=1;
                    break;
                }
                else {
                    check[z]=1;
                }
            }
        }
        if (error == 1){
            break;
        }
    }

#ifdef DEBUG_PRINT
    printf("Error in col %d: %d\n",column_num,error);
    printf("Check:");
    for ( y = 0; y < 9; ++y ){
            printf(" %d",check[y]);
    }
    printf("\n");
#endif

    return error;

}

int check_block (int block_num, int matrix[9][9][9])
/*  check if any number duplicates in a 3x3 block
    Block numbering:
    1 2 3
    4 5 6
    7 8 9
*/
{
    int k=0;
    int x=0;
    int x_offset=0;
    int y=0;
    int y_offset=0;
    int z=0;
    int error=0;
    int status=0;
    int check[9];
    /*  init the check vector   */
    for ( y = 0; y < 9; ++y ){
        check[y]=0;
    }
    /*  offset the coordinates of the block by the
        block_num input */
    x_offset=((block_num-1)%3)*3;
    y_offset=((block_num-1)/3)*3;
    /*  check each element of the 3x3 block and if
        it has the status 2 or 3 tick the check vector
        for this number. If the same number is found again
        break from the loop and output an error */
    for ( k = 0; k < 9; ++k ){
        x=(k%3)+x_offset;
        y=(k/3)+y_offset;
        for ( z = 0; z < 9; ++z ){
            /*  get status of the element   */
            status=matrix[x][y][z];
            /*  if status is evaluating(2) or final(3) check    */
            if (status > 1){
                if (check[z]==1){
                    error=1;
                    break;
                }
                else {
                    check[z]=1;
                }
            }
        }
        if (error == 1){
            break;
        }
    }

#ifdef DEBUG_PRINT
    printf("Error in blk %d: %d\n",block_num,error);
    printf("Check:");
    for ( y = 0; y < 9; ++y ){
            printf(" %d",check[y]);
    }
    printf("\n");
#endif

    return error;

}

int sum (int num, int array[]){
    /*  add num of array elements   */
    int i=0;
    int sum=0;
    for ( i = 0; i < num; ++i ){
        sum += array[i];
    }
    return sum;
}

int check_matrix (int en_display, int matrix[9][9][9])
/*  Check all the rows, columns and blocks if any of the numbers
    violate the sudoku rules    */
{
    int i=0;
    int status=0;
    int row_status[9];
    int col_status[9];
    int blk_status[9];
    /*  init the status vectors     */
    for ( i = 0; i < 9; ++i ){
        row_status[i]=0;
        col_status[i]=0;
        blk_status[i]=0;
    }
    for ( i = 0; i < 9; ++i ){
        row_status[i]=check_row(i+1,matrix);
        col_status[i]=check_column(i+1,matrix);
        blk_status[i]=check_block(i+1,matrix);
    }

    if (en_display){
        if (sum(9,row_status) > 0){
            printf("Error in row(s):");
            for ( i = 0; i < 9; ++i ){
                if (row_status[i]==1){
                    printf(" %d",i+1);
                }
            }
            printf(".\n");
        }

        if (sum(9,col_status) > 0){
            printf("Error in column(s):");
            for ( i = 0; i < 9; ++i ){
                if (col_status[i]==1){
                    printf(" %d",i+1);
                }
            }
            printf(".\n");
        }

        if (sum(9,blk_status) > 0){
            printf("Error in block(s):");
            for ( i = 0; i < 9; ++i ){
                if (blk_status[i]==1){
                    printf(" %d",i+1);
                }
            }
            printf(".\n");
        }
    }

    status=sum(9,row_status)+sum(9,col_status)+sum(9,blk_status);
    if (status == 0){
        return 0;
    } else {
        return 1;
    }
}

int remove_candidates (int *cnt, int matrix[9][9][9]){
/*  Sweeps one time trough all the fields in the matrix
    and removes any candidates that do not pass the check -
    same number already exists in the same row, column or block.
    No candidate must be in evaluation mode(2), otherwise function
    exits with error code!    */
    int x=0;
    int y=0;
    int z=0;
    int status=0;
    int m_status=0;
    int error=0;
    int count=0;

    for ( x = 0; x < 9; ++x )
    {
        for ( y = 0; y < 9; ++y )
        {
            for ( z = 0; z < 9; ++z )
            {
                /*  get status of candidate z in field x,y  */
                status=matrix[x][y][z];
                /*  if candidate is begin evaluated(2), and and return error    */
                if (status==2){
                    printf("remove_candidates: Error! Candidate in evaluation mode!\n");
                    error=1;
                    break;
                }
                /*  if candidate is possible(1)    */
                if (status==1){
                    /*  set candidate to evaluate   */
                    matrix[x][y][z]=2;
                    /*  check sudoku rules  */
                    m_status=check_matrix(0,matrix);
                    /*  if check fails, remove candidate, otherwise
                        set it back to possible */
                    if (m_status==1){
                        matrix[x][y][z]=0;
                        count++;
                    } else{
                        matrix[x][y][z]=1;
                    }
                }
            }
            if (error==1){
                break;
            }
        }
        if (error==1){
            break;
        }
    }

    *cnt=count;

    return error;
}

int single_find_check_row (int *stat, int column, int row, int value,  int matrix[9][9][9]){
    int i=0;
    int check[9];
    int status=0;
    /*  scan the row for selected value */
    for ( i = 0; i < 9; ++i ){
        if (matrix[i][row][value]==1){
            check[i]=1;
        } else {
            check[i]=0;
        }
    }
    /*  if selected value is the only one in a row, set it as final
        and the other possible values on this position as not */
    if (sum(9,check)==1){
        for ( i = 0; i < 9; ++i ){
            if (i==value){
                matrix[column][row][i]=3;
            } else {
                matrix[column][row][i]=0;
            }
        }
        status=1;
    }
    *stat=status;
    return 0;
}

int single_find_check_column (int *stat, int column, int row, int value,  int matrix[9][9][9]){
    int i=0;
    int check[9];
    int status=0;
    /*  scan the column for selected value */
    for ( i = 0; i < 9; ++i ){
        if (matrix[column][i][value]==1){
            check[i]=1;
        } else {
            check[i]=0;
        }
    }
    /*  if selected value is the only one in a column, set it as final
        and the other possible values on this position as not */
    if (sum(9,check)==1){
        for ( i = 0; i < 9; ++i ){
            if (i==value){
                matrix[column][row][i]=3;
            } else {
                matrix[column][row][i]=0;
            }
        }
        status=1;
    }
    *stat=status;
    return 0;
}

int single_find_check_square (int *stat, int column, int row, int value,  int matrix[9][9][9]){
    int i=0;
    int check[9];
    int status=0;
    /*  scan the square for selected value */
    for ( i = 0; i < 9; ++i ){
        /*  use modulo to determine the positions in a row (0,1,2)
            and integer division to determine the position in the column (0,1,2)
            For offsets of the square use the same operations on the provided position
            and multiplying it with 3   */
        if (matrix[(i%3)+((column/3)*3)][(i/3)+((row/3)*3)][value]==1){
            check[i]=1;
        } else {
            check[i]=0;
        }
    }
    /*  if selected value is the only one in a square, set it as final
        and the other possible values on this position as not */
    if (sum(9,check)==1){
        for ( i = 0; i < 9; ++i ){
            if (i==value){
                matrix[column][row][i]=3;
            } else {
                matrix[column][row][i]=0;
            }
        }
        status=1;
    }
    *stat=status;
    return 0;
}

int single_find (int *cnt, int matrix[9][9][9]){
/*  Check if a row, column or square has only one possible
    position for the selected candidate and change it to final
    while the others become not candidates  */
    int x=0;
    int y=0;
    int z=0;
    int count=0;
    int status=0;

    /*  check for all positions */
    for ( y = 0; y < 9; ++y )
    {
        for ( x = 0; x < 9; ++x ){
            /*  for each possible value */
            for ( z = 0; z < 9; ++z ){
                /*  if candidate is status not or final - ignore */
                if ((matrix[x][y][z]==0) || (matrix[x][y][z]==3)){
                    continue;
                } else {
                    /*  check if selected candidate only in selected row    */
                    single_find_check_row(&status, x, y, z, matrix);
                    if (status==1){
                        status=0;
                        count++;
                        break;
                    }
                    /*  check if only in column */
                    single_find_check_column(&status, x, y, z, matrix);
                    if (status==1){
                        status=0;
                        count++;
                        break;
                    }
                    /*  check if only in square */
                    single_find_check_square(&status, x, y, z, matrix);
                    if (status==1){
                        status=0;
                        count++;

                    }
                }
            }
        }
    }
    *cnt=count;
    return 0;
}

int pass_to_final (int *cnt, int matrix[9][9][9]){
/*  Sweeps one time trough all the fields in the matrix
    and check if and candidates can be transformed from
    possible to final. This condition is met when only one
    candidate is possible(1) and all others are not candidate(0).    */
    int x=0;
    int y=0;
    int z=0;
    int status=0;
    int not_cnt=0;
    int pass_cnt=0;
    int count=0;

    for ( x = 0; x < 9; ++x )
    {
        for ( y = 0; y < 9; ++y )
        {
            pass_cnt=0;
            not_cnt=0;
            for ( z = 0; z < 9; ++z )
            {
                status=matrix[x][y][z];
                /*  if final(3) stop checking  */
                if (status==3){
                    break;
                }
                if (status==0){
                    not_cnt++;
                }
                if (status==1){
                    pass_cnt++;
                }
            }
            /*  if only one candidate is possible(1) and all the
                others are not(0) set the candidate to final(3) */
            if ((not_cnt==8) && (pass_cnt==1)){
                count++;
                for ( z = 0; z < 9; ++z ){
                    if (matrix[x][y][z]==1){
                        matrix[x][y][z]=3;
                    }
                }
            }
        }
    }

    *cnt=count;

    return 0;
}

int display_candidate_status(int x, int y,int matrix[9][9][9]){
    /*  debug tool that displays the status of
        the selected position in the matrix */
    int z=0;
    printf("Candidate [%d][%d]:",x,y);
    for ( z = 0; z < 9; ++z ){
        printf(" %d",matrix[x-1][y-1][z]);
    }
    printf(".\n");
    return 0;
}

void clear_screen (void) {
#ifdef LINUX
    system("clear");
#else
    system("cls");
#endif // LINUX
}

int analyitic_solver (int matrix[9][9][9]){
    /*  Determine the values of the matrix using the reduction
        of the number of possible candidates. */
    int rc_count;
    int pf_count;
    int sf_count;
    do {

        remove_candidates(&rc_count,matrix);
        pass_to_final(&pf_count,matrix);
        single_find (&sf_count,matrix);

        clear_screen();
        printf("Analytic phase:\n");
        display_matrix(1,matrix);
        printf("Candidates finalized: %d\n",rc_count);
        printf("Candidates removed: %d\n",pf_count);
        printf("Candidates singled: %d\n",sf_count);

    } while ((rc_count>0) || (pf_count>0) || (sf_count>0));

    return 0;
}

int user_matrix_input (int *exit, int matrix[9][9][9]){
    int done=0;
    int ch;
    int ch_cnt;
    int in_error;
    int row=0;
    int select_line=1;
    int buffer[9];
    int i=0;
    int j=0;
    *exit=0;
    while (done == 0){
        clear_screen();
        printf("Sudoku matrix input.\n");
        display_matrix(0,matrix);
        printf("r - run\n");
        printf("e - exit\n");
        /*  error display   */
        if (in_error == 1) {
            printf("Bad input. Please enter exactly one number 1-9.\n");
        } else if (in_error == 2) {
            printf("Bad input. Please enter exactly 9 numbers 0-9.\n");
        } else if (in_error == 3) {
            printf("Bad input. Incorrect number of inputs.\n");
        }
        /* display selected screen  */
        if (select_line==1) {
            printf("Select line (1-9) and hit Enter:");
        } else if (select_line==0) {
            printf("Enter 9 numbers for row %d and hit Enter",row);
            printf("(1-9) - set numbers, 0 - missing value\n");
            printf("Example: 010050230 :");
        }
        /*  store first nine inputs to the array    */
        ch_cnt = 0;
        in_error = 0;
        do
        {
            ch = fgetc(stdin);
            /*  if new line pass the storing    */
            if (ch == '\n'){
                continue;
            }
            else if (ch_cnt < 9){
                buffer[ch_cnt]=ch;
            }
            ch_cnt++;
        } while (ch != '\n');

        /*  if 1 input character    */
        if (ch_cnt==1){
            /*  if exit selected */
            if (buffer[0]=='e'){
                *exit=1;
                break;
            /*  if run selected */
            } else if (buffer[0]=='r'){
                break;
                done=1;
            /* if row selection, character should be number 1-9    */
            } else if ((select_line==1) && (buffer[0]<='9') && (buffer[0]>'0')) {
                row=buffer[0]-'0';
                select_line=0;
            /* otherwise report error   */
            } else {
                in_error=1;
            }
        /*  if 9 input characters   */
        } else if (ch_cnt==9){
            if (select_line==0){
                /*  check if all characters 0-9 */
                for ( i = 0; i < 9; ++i ){
                    if (!(buffer[i] <= '9') && (buffer[i] >= '0')) {
                        in_error=2;
                        break;
                    }
                }
                /*  if characters ok input them to the matrix   */
                if (in_error==0){
                    for ( i = 0; i < 9; ++i ){
                        /*  if input is a valid final number  */
                        if (buffer[i]>'0'){
                            /*  scan trough all potential number candidates for this position    */
                            for ( j = 0; j < 9; ++j ){
                                if (j==(buffer[i]-'0'-1)){
                                    /*  set selected number to final    */
                                    matrix[i][row-1][j]=3;
                                } else {
                                    /*  and the rest to not candidate   */
                                    matrix[i][row-1][j]=0;
                                }
                            }
                        }
                    }
                    select_line=1;
                }
            } else {
                in_error=3;
            }
        /*  if other number of inputs   */
        } else {
            in_error=3;
        }

    }
    return 0;
}

int main()
{
    /*  matrix holds the status for each value on each position:
        0 - not candidate,
        1 - possible candidate,
        2 - evaluating candidate,
        3 - final candidate */
    int matrix [9][9][9];
    int exit;

    set_const_matrix(1,matrix);

    user_matrix_input(&exit,matrix);
    if (exit){
        return 0;
    }
//    finished_correct_matrix(matrix);
//    display_matrix(matrix);
//        getchar();
//    unfinished_solvable_matrix(matrix);
//    display_matrix(matrix);

    check_matrix(1,matrix);

    analyitic_solver(matrix);

    /*end by inputing any key*/
    getchar();
    return 0;
}
