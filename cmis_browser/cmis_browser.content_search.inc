<?php 

function cmis_browser_search($term, $path){
  module_load_include('api.inc', 'cmis');
  $parts = explode('/', $_GET['q']);
  $path = implode('/', array_slice($parts, 4));
    
  try {
    $repository = cmis_get_repository();
    debug($path);
    $folder_object = cmisapi_getObjectByPath($repository->repositoryId, '/'.$path);
    debug($folder_object);
  }catch (CMISException $e) {
    cmis_error_handler('cmis_browser_search', $e);
  }
  return 'Search for: '.$term.' In tree: '.$path;
}