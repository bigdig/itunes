<?php
// $Id$

/**
 * Implementation of hook_views_default_views().
 */
function itunes_views_default_views() {
  $view = new view;
  $view->name = 'itunes';
  $view->description = "A demo feed for the iTunes module. You can either enable this and modify it to suit your needs or, if you don't like the name, clone it and make your changes that way.";
  $view->tag = '';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('row_plugin', 'node');
  $handler->override_option('row_options', array(
    'teaser' => 1,
    'links' => 1,
    'comments' => 0,
  ));
  $handler = $view->new_display('feed', 'Feed', 'feed_1');
  $handler->override_option('style_plugin', 'itunes_rss');
  $handler->override_option('style_options', array(
    'mission_description' => FALSE,
    'description' => '',
    'subtitle' => '',
    'summary' => '',
    'author' => '',
    'copyright' => '',
    'image_url' => '',
    'explicit' => '0',
    'block' => 0,
    'owner_name' => '',
    'owner_email' => '',
    'categories' => array(
      '0' => '',
      '1' => '',
      '2' => '',
    ),
  ));
  $handler->override_option('row_plugin', 'node_rss');
  $handler->override_option('row_options', array(
    'item_length' => 'default',
  ));
  $handler->override_option('path', 'itunes/feed');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'weight' => 0,
  ));
  $handler->override_option('displays', array(
    'default' => 'default',
    'page_1' => 'page_1',
  ));
  $handler->override_option('sitename_title', FALSE);
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('title', 'iTunes');
  $handler->override_option('path', 'itunes/feed');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'weight' => 0,
  ));
   $views[$view->name] = $view;

  return $views;
}