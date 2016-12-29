/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

 // @Generated by gentest/gentest.rb from gentest/fixtures/YGAlignContentTest.html

var Yoga = Yoga || require("../../sources/entry-" + process.env.TEST_ENTRY);

it("garbage_collection", function () {
  (function () {
    var a = new Yoga.Node();
    var b = new Yoga.Node();

    a.release();
    b.release();
  }());

  (typeof gc !== "undefined") && gc(); // only has an actual effect on Node.js environments running the native build
  console.assert(0 === Yoga.getInstanceCount(), "0 === Yoga.getInstanceCount() (" + Yoga.getInstanceCount() + ")");
});

it("garbage_collection_via_child", function () {
  (function () {
    var a = new Yoga.Node();
    var b = new Yoga.Node();

    a.insertChild(b, 0);
    var c = a.getChild(0);

    a.freeRecursive();
    b.release();
    c.release();
  }());

  (typeof gc !== "undefined") && gc(); // only has an actual effect on Node.js environments running the native build
  console.assert(0 === Yoga.getInstanceCount(), "0 === Yoga.getInstanceCount() (" + Yoga.getInstanceCount() + ")");
});

it("garbage_collection_common_workflow", function () {
  (function () {
    var root = new Yoga.Node();

    (function () {
      var child = new Yoga.Node();

      root.insertChild(child, 0);
      child.release(); // release the reference
    })();

    root.freeRecursive();
  }());

  (typeof gc !== "undefined") && gc(); // only has an actual effect on Node.js environments running the native build
  console.assert(0 === Yoga.getInstanceCount(), "0 === Yoga.getInstanceCount() (" + Yoga.getInstanceCount() + ")");
});
