import js from "@eslint/js";
import stylisticJs from "@stylistic/eslint-plugin-js";
import stylisticTs from "@stylistic/eslint-plugin-ts";
import ts from "@typescript-eslint/eslint-plugin";
import parserTs from "@typescript-eslint/parser";
import importPlugin from "eslint-plugin-import";
import react from "eslint-plugin-react";
import reactHooks from "eslint-plugin-react-hooks";
import reactRefresh from "eslint-plugin-react-refresh";
import eslintPluginSortKeysFix from "eslint-plugin-sort-keys-fix";
import globals from "globals";


export default [
    { ignores: [] },
    {
        files: ["**/*.{js,jsx,ts,tsx}"],
        languageOptions: {
            globals: globals.browser,
            parser: parserTs,
            parserOptions: {
                ecmaFeatures: { jsx: true },
                ecmaVersion: "latest",
                sourceType: "module"
            }
        },
        plugins: {
            "@stylistic/js": stylisticJs,
            "@stylistic/ts": stylisticTs,
            "@typescript-eslint": ts,
            "importPlugin": importPlugin,
            react,
            "react-hooks": reactHooks,
            "react-refresh": reactRefresh,
            "sort-keys-fix": eslintPluginSortKeysFix
        },
        rules: {
            ...js.configs.recommended.rules,
            ...react.configs.recommended.rules,
            ...react.configs["jsx-runtime"].rules,
            ...reactHooks.configs.recommended.rules,
            "@stylistic/js/arrow-spacing": ["error", { "after": true, "before": true }],
            "@stylistic/js/brace-style": ["error", "1tbs", { "allowSingleLine": true }],
            "@stylistic/js/comma-dangle": ["error", "never"],
            "@stylistic/js/comma-spacing": ["error", { "after": true }],
            "@stylistic/js/eol-last": ["error", "always"],
            "@stylistic/js/indent": ["error", 4],
            "@stylistic/js/jsx-quotes": ["error", "prefer-double"],
            "@stylistic/js/object-curly-spacing": ["error", "always"],
            "@stylistic/js/quotes": ["error", "double", { "allowTemplateLiterals": "always" }],
            "@stylistic/js/semi": ["error", "always"],
            "eqeqeq": ["error", "always"],
            "importPlugin/newline-after-import": ["error", { "considerComments": true, "count": 2, "exactCount": true }],
            "importPlugin/order": ["error", {
                "alphabetize": { "caseInsensitive": false, "order": "asc" },
                "groups": [[
                    "index",
                    "type",
                    "object",
                    "external",
                    "internal",
                    "sibling",
                    "parent",
                    "builtin",
                    "unknown"
                ]],
                "named": true,
                "newlines-between": "never"
            }],
            "react/prop-types": "off",
            "sort-keys-fix/sort-keys-fix": ["error", "asc", {
                "caseSensitive": true,
                "natural": true
            }]
        },
        settings: { react: { version: "18.3" } }
    }
];
