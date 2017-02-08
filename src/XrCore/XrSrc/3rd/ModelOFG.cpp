#define __MODELOFG_C__
#include "ModelOFG.h"
#include "../Platform/XrOS.h"

#define NONE_MODEL  (Model_SV *)0
Model_SV* import_vertex_from_file(char *filename)
{
	Model_SV *model=NULL;

	FILE *fp = fopen(filename, "rb");
	if(!fp)
	{
		model = NONE_MODEL;
		return model;
	}
	model = new Model_SV;
	fread(&model->vertex_total, sizeof(int), 1, fp);
	fread(&model->index_total, sizeof(int), 1, fp);
	model->index_total = model->index_total*3;
	
	model->vertex_list = (Model_SV_Vertex*)malloc(model->vertex_total*sizeof(Model_SV_Vertex));
	model->index_list = (index_type*)malloc(model->index_total*sizeof(index_type));

	if(model->vertex_list==0 || model->index_list==0)
	{
		fclose(fp);
		return NONE_MODEL;
	}

	fread(model->vertex_list, sizeof(Model_SV_Vertex), model->vertex_total, fp);
	fread(model->index_list, sizeof(index_type), model->index_total, fp);
	fclose(fp);
	return model;
}

void saveTxtFile(char *filename,Model_SV* model)
{
    char file_path[80] = "./svres/OFGmodel/";

	char file_name_final[80];
	sprintf(file_name_final,"%s%s",file_path,filename);
	FILE *fp = fopen(file_name_final, "wb");
		if(!fp)
		{
			
			return;
		}


    int tempUint;
	fprintf( fp , "IndexNum:%d,\r\n" ,model->index_total);

	fprintf( fp , "VertexNum:%d,\r\n" ,model->vertex_total);

	fprintf(fp,"\r\n");
	fprintf(fp,"vertex:=========================\r\n");
    
    int i;
    for(i = 0;i < model->vertex_total*8  ;i ++)
    {
    	fprintf( fp , "%f," ,*( (float *)(model->vertex_list)+i));			

		if(i%8==7)
		fprintf(fp, "\r\n");
    }

		
	fprintf(fp,"\r\n");
	fprintf(fp,"Index:=========================\r\n");

	    for(i = 0;i < model->index_total  ;i ++)
    {
    	fprintf( fp , "%d," , *((model->index_list)+i));			

		if(i%8==7)
		fprintf(fp, "\r\n");
    }
   // printf("\r\n read [%d] over",num);
    
    if(fp != NULL)
    {
    	if(fileno(fp)>0)
    	{	  
    		printf("\r\n fp_table = %d",fp);	 
    		fclose(fp);
    	 }		  
    return;
    }	
    

	return;


}



Model_SV *ofgCreateModel(char *filename, double scale, int loadVBO)
{
    Model_SV *OFGmodel;
	Model_SV_Vertex *pVertex;
	static int index=0;
	char *name[4]={"1.txt","2.txt","3.txt","4.txt"};
	
	int i =0;
    OFGmodel = import_vertex_from_file(filename);
	if(0 == OFGmodel)
	{
	    printf("\r\n Load OFG Model %s  Failed",filename);
		return 0;
	}
    //process scale
    for(i=0;i<OFGmodel->vertex_total;i++)
    {
       pVertex = OFGmodel->vertex_list+i;
	   pVertex->vertex[0] *= scale;
	   pVertex->vertex[1] *= scale;
	   pVertex->vertex[2] *= scale;
	   if(pVertex->normal[0] <= 0.0401941&&pVertex->normal[0] >= 0.0401939)
	   	{
	   	pVertex->normal[0] =1.0;
	   	}
    }


  // saveTxtFile(name[index],OFGmodel);

//    index++;
   return OFGmodel;
}




