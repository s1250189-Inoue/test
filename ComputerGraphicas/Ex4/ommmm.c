for(i=0;i< nEges; i++){
  face[edge[i].fidL].fid[face[i].fidL].nF]=edge[i].fidR;
  face[edge[i].fidR].fid[face[i].fidR].nF]=edge[i].fidL;

  face[edge[i].fidL].nF++;
  face[edge[i].fidR].nF++;
}
