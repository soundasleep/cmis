<?php 

function cmis_browser_search($term, $path){
  module_load_include('api.inc', 'cmis');
  module_load_include('content_get.inc', 'cmis_browser');

  $parts = explode('/', $_GET['q']);
  $path = implode('/', array_slice($parts, 4));
  $args = func_get_args();
    
  try {
    $repository = cmis_get_repository();
    $folder_object = cmisapi_getObjectByPath($repository->repositoryId, '/'.$path);
        $matches = array();

    foreach (array('cmis:folder', 'cmis:document') as $cmis_base_type) {
      try {
        $cmis_objects = cmisapi_query($repository->repositoryId,
          //All children of the current folder
          sprintf('SELECT * FROM %s WHERE IN_TREE(\'%s\') AND (cmis:name like \'%s\' OR CONTAINS(\'%s\'))',
                  $cmis_base_type, $folder_object->id, '%'. $term .'%', $term)
          //Only children of the current folder
/*          sprintf('SELECT * FROM %s WHERE IN_TREE(\'%s\') AND (cmis:name like \'%s\' OR CONTAINS(\'%s\'))',
                  $cmis_base_type, $folder_object->id, '%'. $term .'%', $term)*/
        );
      }
      catch (CMISException $e) {
        cmis_error_handler('cmis_path_autocomplete', $e);
        continue;
      }
    }

  }catch (CMISException $e) {
    cmis_error_handler('cmis_browser_search', $e);
  }
  $hook = 'cmis_browser';
  return theme($hook, array(
    'children' => $cmis_objects->objectList,
    'bcarray' => '',
    'type' => !empty($_GET['type']) ? check_plain($_GET['type']) : '',
  ));
  //debug($matches);
  //return 'Search for: '.$term.' In tree: '.$path;
}