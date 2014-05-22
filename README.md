Drupal CMIS
===========

This is a port of the original [Drupal CMIS project](https://drupal.org/project/cmis) with some additional fixes.

### Installation

Right now you should just be able to drop this directly into an existing Drupal installation to replace the CMIS module with no ill effects. Not tested.

Make sure that you also have the [`cmis-phplib` library](https://people.apache.org/~richardm/chemistry/phpclient/0.2.0-RC1/) installed into your `sites/all/libraries/cmis-phplib` directory.

### Feature changes

* _CMIS Check_ link is actually visible in _Configure_ menu
* Content field type `text_textfield` [can be synced](https://drupal.org/node/2074063#comment-7797843)
* [#2219095](https://drupal.org/node/2219095): Prevent _Invalid node ref - does not contain forward slash:_ server error occurring when deleting nodes in `_cmis_sync_cmis_drupal_handle_deletes()`
* [#1932658](https://drupal.org/node/1932658): Configurable default text format for CMIS content_field

### Developer changes

* Uses [EditorConfig](http://editorconfig.org) for consistent whitespace throughout

### Original project

The original project Git: http://git.drupal.org/project/cmis.git
