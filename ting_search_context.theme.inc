<?php

/**
 * @file
 * Theme functions used with the ting search context.
 */

/**
 * Implements default preprocess function for the search context.
 */
function template_preprocess_ting_search_context(&$vars, $hook) {
  // Add Javascript settings
  drupal_add_js(array('ting_search_context_id' => $vars['context_id']), 'setting');
  drupal_add_js(array('ting_search_context_position' => $vars['position']), 'setting');

  // Add JavaScript and CSS using wrapper functions.
  _ting_search_context_add_javascript();
  _ting_search_context_add_css();
}

/**
 * Implements default preprocess function for the search context content.
 */
function template_preprocess_ting_search_context_content(&$vars, $hook) {
  $node = $vars[node];

  //Image
  $field_name = ting_search_context_get_image_field_name($node);
  $image = field_view_field('node', $node, $field_name, array(
    'label' => 'hidden',
    'settings' => array(
      'image_style' => 'ting_search_context',
    ),
    ));
  $vars['image'] = drupal_render($image);

  //URL
  $webtrends_paramater = 'WT.cg_n=searchcontext';
  if ($node->type == 'ding_search_context_link') {
    $link_field = field_get_items('node', $node, 'field_search_context_link');
    $link = empty($link_field [0]['url']) ? 0 : $link_field[0]['url'];
    $url = str_replace('"', '%22', $link ); // Quotes inside search queries need to be escaped

    if (strpos($url, '?') == false) {
      $url .= '?WT.cg_n=searchcontext';
    } else {
      $url .= '&WT.cg_n=searchcontext';
    }
  } else {
    $url = url(drupal_get_path_alias('node/' . $node->nid), array('absolute' => TRUE, 'query' => array ('WT.cg_n' => 'searchcontext')));
  }

  $vars['url'] = $url;

  // Title
  $title = check_plain($node->title);
  if (strlen($title) > 20) {
    $title = substr($title, 0, 18) . '..';
  }
  $vars['title'] = $title;
}

