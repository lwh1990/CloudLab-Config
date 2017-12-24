#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pnetcdf.h>
#include <mpi.h>
#include <math.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

static void err(int status, int lineno)
{
    fprintf(stderr,"Error at line %d: %s\n", lineno, ncmpi_strerror(status));
    MPI_Abort(MPI_COMM_WORLD, 1);
}

inline void genstatmeta(float *data, long len, float *meta)
{
    float mmax, mmin, sum=0;
    long i;

    mmax = mmin = data[0];
    for(i = 0; i < len; i++)
    {
        mmax = MAX(mmax, data[i]);
        mmin = MIN(mmin, data[i]);
        sum += data[i];
    }
    meta[0] = mmax;
    meta[1] = mmin;
    meta[2] = sum / len;
}

int main(int argc, char **argv)
{
    long i, j, len;
    int rank, nprocs, ret, flag = 1;
    int ncfile, ndims, nvars, ngatts, unlimited;
    int var_ndims, var_natts;
    MPI_Offset *dim_sizes, var_size;
    MPI_Offset *start, *count;
    char filename[256], varname[256];
    int *dimids = NULL;
    nc_type type;
    float *data = NULL, sum = 0.0, mean, std;
    double t1, t2;
    int ncid, varid, varid1, data_dimid, meta_dimid;
    float mmax, mmin, meta[3];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    strcpy(filename, "500g.nc");

    ret = ncmpi_open(MPI_COMM_WORLD, filename, NC_NOWRITE, MPI_INFO_NULL, &ncfile);
    if(ret != NC_NOERR) err(ret, __LINE__);

    ret = ncmpi_inq(ncfile, &ndims, &nvars, &ngatts, &unlimited);
    if(ret != NC_NOERR) err(ret, __LINE__);
   // printf("ndims=%d, nvars=%d, ngatts=%d, unlimited=%d\n",
   //         ndims, nvars, ngatts, unlimited);

    dim_sizes = (MPI_Offset*)calloc(ndims, sizeof(MPI_Offset));

    for(i = 0; i < ndims; i++)
    {
        ret = ncmpi_inq_dimlen(ncfile, i, &(dim_sizes[i]));
        if(ret != NC_NOERR) err(ret, __LINE__);
       // printf("dim_sizes[%d]=%d\n", i, dim_sizes[i]);
    }

    ret = ncmpi_inq_varndims(ncfile, 2, &var_ndims);
    if(ret != NC_NOERR) err(ret, __LINE__);
    //printf("var_ndims = %d\n", var_ndims);

    ret = ncmpi_inq_var(ncfile, 2, varname, &type, &var_ndims, dimids, &var_natts);
    if(ret != NC_NOERR) err(ret, __LINE__);

    start = (MPI_Offset*)calloc(var_ndims, sizeof(MPI_Offset));
    count = (MPI_Offset*)calloc(var_ndims, sizeof(MPI_Offset));

    count[1] = dim_sizes[0];
    count[2] = dim_sizes[1];
    start[1] = 0;
    start[2] = 0;
    len = 20 * count[1] * count[2];
    data = (float*) malloc (len*sizeof(float));

    if (flag == 0)
    {
        printf("===origin===\n");
        /* task1 read */
        start[0] = 1979;
        count[0] = 20;
        t1 = MPI_Wtime();
        ret = ncmpi_get_vara_float_all(ncfile, 2, start, count, data);
        if(ret != NC_NOERR) err(ret, __LINE__);
        t2 = MPI_Wtime();
        if(rank==0)printf("task1 readtime = %f\n", t2-t1);

        /* task1 compute mean*/
        t1 = MPI_Wtime();
        for(i = 0; i < len; i++)
        {
            sum += data[i];
        }
        mean = sum / len;
        t2 = MPI_Wtime();
        if(rank==0)printf("task1 comptime = %f\n", t2-t1);

        /* task2 read */
        start[0] = 1979;
        count[0] = 20;
        t1 = MPI_Wtime();
        ret = ncmpi_get_vara_float_all(ncfile, 2, start, count, data);
        if(ret != NC_NOERR) err(ret, __LINE__);
        t2 = MPI_Wtime();
        if(rank==0)printf("task2 readtime = %f\n", t2-t1);

        /* task2 compute std */
        t1 = MPI_Wtime();
        for(i = 0; i < len; i++)
        {
            sum += data[i];
        }
        mean = sum / len;
        for(i = 0; i < len; i++)
        {
            sum += pow((data[i]-mean), 2);
        }
        std = sqrt(sum/(len - 1));
        t2 = MPI_Wtime();
        if(rank==0)printf("task2 comptime = %f\n", t2-t1);

        /* task3 read */
        start[0] = 1989;
        count[0] = 20;
        t1 = MPI_Wtime();
        ret = ncmpi_get_vara_float_all(ncfile, 2, start, count, data);
        if(ret != NC_NOERR) err(ret, __LINE__);
        t2 = MPI_Wtime();
        if(rank==0)printf("task3 readtime = %f\n", t2-t1);

       /* task3 compute mean*/
        t1 = MPI_Wtime();
        for(i = 0; i < len; i++)
        {
            sum += data[i];
        }
        mean = sum / len;
        t2 = MPI_Wtime();
        if(rank==0)printf("task3 comptime = %f\n", t2-t1);

        /* task4 read */
        start[0] = 1989;
        count[0] = 20;
        t1 = MPI_Wtime();
        ret = ncmpi_get_vara_float_all(ncfile, 2, start, count, data);
        if(ret != NC_NOERR) err(ret, __LINE__);
        t2 = MPI_Wtime();
        if(rank==0)printf("task4 readtime = %f\n", t2-t1);

        /* task4 compute std */
        t1 = MPI_Wtime();
        for(i = 0; i < len; i++)
        {
            sum += data[i];
        }
        mean = sum / len;
        for(i = 0; i < len; i++)
        {
            sum += pow((data[i]-mean), 2);
        }
        std = sqrt(sum/(len - 1));
        t2 = MPI_Wtime();
        if(rank==0)printf("task4 comptime = %f\n", t2-t1);
    }
    else
    {
        printf("===optimal===\n");
        /* task1 read */
        start[0] = 1979;
        count[0] = 20;
        t1 = MPI_Wtime();
        ret = ncmpi_get_vara_float_all(ncfile, 2, start, count, data);
        if(ret != NC_NOERR) err(ret, __LINE__);
        t2 = MPI_Wtime();
        if(rank==0)printf("task1 readtime = %f\n", t2-t1);

        /* task1 compute mean*/
        t1 = MPI_Wtime();
        for(i = 0; i < len; i++)
        {
            sum += data[i];
        }
        mean = sum / len;
        t2 = MPI_Wtime();
        if(rank==0)printf("task1 comptime = %f\n", t2-t1);

        /* task1 cache */      
        t1 = MPI_Wtime();
        ret = ncmpi_create(MPI_COMM_WORLD, "/ssd/cache.nc", NC_CLOBBER, MPI_INFO_NULL, &ncid);
        if(ret != NC_NOERR) err(ret, __LINE__);
        
        ret = ncmpi_def_dim(ncid, "len", len, &data_dimid);
        if(ret != NC_NOERR) err(ret, __LINE__);

        ret = ncmpi_def_var(ncid, "data", NC_FLOAT, 1, &data_dimid, &varid);
        if(ret != NC_NOERR) err(ret, __LINE__);

        ret = ncmpi_def_dim(ncid, "metalen", 3, &meta_dimid);
        if(ret != NC_NOERR) err(ret, __LINE__);

        ret = ncmpi_def_var(ncid, "meta", NC_FLOAT, 1, &meta_dimid, &varid1);
        if(ret != NC_NOERR) err(ret, __LINE__);

        ret = ncmpi_enddef(ncid);
        if(ret != NC_NOERR) err(ret, __LINE__);

        genstatmeta(data, len, meta);

        ret = ncmpi_put_var_float_all(ncid, varid, data);
        if(ret != NC_NOERR) err(ret, __LINE__);

        ret = ncmpi_put_var_float_all(ncid, varid1, meta);
        if(ret != NC_NOERR) err(ret, __LINE__);
        
        ret = ncmpi_close(ncid);
        if(ret != NC_NOERR) err(ret, __LINE__);
    
        t2 = MPI_Wtime();
        if(rank==0)printf("task2 cachetime = %f\n", t2-t1);

        /* task2 read */
        t1 = MPI_Wtime();
        ret = ncmpi_open(MPI_COMM_WORLD, "/ssd/cache.nc", NC_NOWRITE, MPI_INFO_NULL, &ncid);
        if(ret != NC_NOERR) err(ret, __LINE__);
        
      /*int tmp;
        ret = ncmpi_inq_dimlen(ncid, 0, &tmp);
        if(ret != NC_NOERR) err(ret, __LINE__);
        printf("test len=%d\n", tmp);*/

        ret = ncmpi_get_var_float_all(ncid, 0, data);
        if(ret != NC_NOERR) err(ret, __LINE__);
        t2 = MPI_Wtime();
        if(rank==0)printf("task2 readtime = %f\n", t2-t1);

        /* task2 compute std */
        t1 = MPI_Wtime();
        ret = ncmpi_get_var_float_all(ncid, 1, meta);
        if(ret != NC_NOERR) err(ret, __LINE__);
        mean = meta[2];
        for(i = 0; i < len; i++)
        {
            sum += pow((data[i]-mean), 2);
        }
        std = sqrt(sum/(len - 1));
        t2 = MPI_Wtime();
        if(rank==0)printf("task2 comptime = %f\n", t2-t1);

        /* task3 read */
        start[0] = 1999;
        count[0] = 10;
        t1 = MPI_Wtime();
        // read new data from PFS
        ret = ncmpi_get_vara_float_all(ncfile, 2, start, count, data);
        if(ret != NC_NOERR) err(ret, __LINE__);
      
        // read meta from BB
        ret = ncmpi_get_var_float_all(ncid, 1, meta);
        if(ret != NC_NOERR) err(ret, __LINE__);
        mean = meta[2];
        t2 = MPI_Wtime();
        if(rank==0)printf("task3 readtime = %f\n", t2-t1);

        /* task3 compute mean */
        t1 = MPI_Wtime();
        sum = 0;
        for(i = 0; i < len/2; i++)
        {
            sum += data[i]; 
        }
        sum += mean * len/2;
        mean = sum / len; 
        t2 = MPI_Wtime();
        if(rank==0)printf("task3 comptime = %f\n", t2-t1);

        ret = ncmpi_close(ncid);
        if(ret != NC_NOERR) err(ret, __LINE__);

        /* task3 cache */
        t1 = MPI_Wtime();
        ret = ncmpi_create(MPI_COMM_WORLD, "/ssd/cache1.nc", NC_CLOBBER, MPI_INFO_NULL, &ncid);
        if(ret != NC_NOERR) err(ret, __LINE__);
        
        ret = ncmpi_def_dim(ncid, "len", len/2, &data_dimid);
        if(ret != NC_NOERR) err(ret, __LINE__);

        ret = ncmpi_def_var(ncid, "data", NC_FLOAT, 1, &data_dimid, &varid);
        if(ret != NC_NOERR) err(ret, __LINE__);

        ret = ncmpi_def_dim(ncid, "metalen", 3, &meta_dimid);
        if(ret != NC_NOERR) err(ret, __LINE__);

        ret = ncmpi_def_var(ncid, "meta", NC_FLOAT, 1, &meta_dimid, &varid1);
        if(ret != NC_NOERR) err(ret, __LINE__);

        ret = ncmpi_enddef(ncid);
        if(ret != NC_NOERR) err(ret, __LINE__);

        genstatmeta(data, len/2, meta);

        ret = ncmpi_put_var_float_all(ncid, varid, data);
        if(ret != NC_NOERR) err(ret, __LINE__);

        ret = ncmpi_put_var_float_all(ncid, varid1, meta);
        if(ret != NC_NOERR) err(ret, __LINE__);
        
        ret = ncmpi_close(ncid);
        if(ret != NC_NOERR) err(ret, __LINE__);
    
        t2 = MPI_Wtime();
        if(rank==0)printf("task3 cachetime = %f\n", t2-t1);

        /* task4 read */
        t1 = MPI_Wtime();
        int ncid1,ncid2;
        float mean1;
        MPI_Offset s=0, c=len/2;
        ret = ncmpi_open(MPI_COMM_WORLD, "/ssd/cache.nc", NC_NOWRITE, MPI_INFO_NULL, &ncid1);
        if(ret != NC_NOERR) err(ret, __LINE__);
        ret = ncmpi_open(MPI_COMM_WORLD, "/ssd/cache1.nc", NC_NOWRITE, MPI_INFO_NULL, &ncid2);
        if(ret != NC_NOERR) err(ret, __LINE__);
        
        // read data from BB
        ret = ncmpi_get_vara_float_all(ncid1, 0, &s, &c,data);
        if(ret != NC_NOERR) err(ret, __LINE__);
        ret = ncmpi_get_var_float_all(ncid2, 0, data+len/2);
        if(ret != NC_NOERR) err(ret, __LINE__);
       
        // read meta from BB
        ret = ncmpi_get_var_float_all(ncid1, 1, meta);
        if(ret != NC_NOERR) err(ret, __LINE__);
        mean = meta[2];
        ret = ncmpi_get_var_float_all(ncid2, 1, meta);
        if(ret != NC_NOERR) err(ret, __LINE__);
        mean1 = meta[2];     

        t2 = MPI_Wtime();
        if(rank==0)printf("task4 readtime = %f\n", t2-t1);

        /* task4 compute std */
        t1 = MPI_Wtime();
        mean = (mean*len/2 + mean1*len/2)/len;
        sum = 0;
        for(i = 0; i < len; i++)
        {
            sum += pow((data[i]-mean), 2);
        }
        std = sqrt(sum/(len - 1));
        t2 = MPI_Wtime();
        if(rank==0)printf("task4 comptime = %f\n", t2-t1);

        ret = ncmpi_close(ncid1);
        if(ret != NC_NOERR) err(ret, __LINE__);
        ret = ncmpi_close(ncid2);
        if(ret != NC_NOERR) err(ret, __LINE__);
 }

    ret = ncmpi_close(ncfile);
    if(ret != NC_NOERR) err(ret, __LINE__);
    
    free(data);
    MPI_Finalize();
    return 0;
}
