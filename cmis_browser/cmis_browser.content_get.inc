<?php

/**
 * Build cmis_browser browse page.
 *
 */
function cmis_browser_content_get() {
  module_load_include('api.inc', 'cmis');
  module_load_include('utils.inc', 'cmis_browser');

  // Invoke CMIS service
  try {
    $repository = cmis_get_repository();
    $object = _cmis_browser_content_object_from_request($repository);

    switch ($object->properties['cmis:baseTypeId']) {
      case 'cmis:document':
        return _cmis_browser_content_get_document($repository, $object);
        break;
      case 'cmis:folder':
        return _cmis_browser_content_get_folder($repository, $object, array_slice(explode('/', $_GET['q']), 2));
        break;
      default:
        throw new CMISException(t('Unable to handle cmis object @object_id of type @object_type', array(
          '@object_id' => $object->id,
          '@object_type' => $object->type
        )));
    }
  }
  catch (CMISException $e) {
    cmis_error_handler('cmis_browser', $e);
    return '';
  }
}

/**
 * CMIS document download handler.
 *
 */
function _cmis_browser_content_get_document($repository, $object) {
  module_load_include('api.inc', 'cmis');

  try {
    $content = cmisapi_getContentStream($repository->repositoryId, $object->id);
  }
  catch (CMISException $e) {
    cmis_error_handler('cmis_browser_content_get', $e);
    drupal_add_http_header('', 'HTTP/1.1 503 Service unavailable');
    exit();
  }

  if (ob_get_level()) {
    ob_end_clean();
  }

  drupal_add_http_header('Cache-Control', 'no-cache, must-revalidate');
  drupal_add_http_header('Content-type', $object->properties['cmis:contentStreamMimeType']);
  if ($object->properties['cmis:contentStreamMimeType'] != 'text/html') {
    drupal_add_http_header('Content-Disposition', 'attachment; filename="'. $object->properties['cmis:name'] .'"');
  }


  print($content);

  exit();
}

/**
 * CMIS folder browser handler.
 *
 */
function _cmis_browser_content_get_folder($repository, $object) {
  try {
    $children = cmisapi_getChildren($repository->repositoryId, $object->id)->objectList;
  }
  catch (CMISException $e) {
    cmis_error_handler('cmis_browser', $e);
    return '';
  }
  $hook = (!empty($_GET['type']) && $_GET['type'] == 'popup') ? 'cmis_browser_popup' : 'cmis_browser';
  return theme($hook, array(
    'children' => $children,
    'bcarray' => explode('/',substr($object->properties['cmis:path'],1)),
    'type' => !empty($_GET['type']) ? check_plain($_GET['type']) : '',
  ));
}
