import models from "../../models/Index.js";
import { configSchema } from "../../types/configs.js";
import { Router } from "express";


const config = Router();

config.get("/", async (req, res, next) => {
    try {
        const config = await models.Configuration.findAll();
        res.status(200).json(config);
    } catch (error) {
        next(error);
    }
});

config.get("/:id", async (req, res, next) => {
    try {
        const config = await models.Configuration.findByPk(req.params.id);
        if (!config) {
            throw new Error(`config entry with id: ${req.params.id} not found`);
        }
        res.status(200).json(config);
    } catch (error) {
        next(error);
    }
});

config.post("/", async (req, res, next) => {
    try {
        const newconfig = new models.Configuration(configSchema.parse(req.body));
        await newconfig.save();
        res.status(201).json(newconfig);
    } catch (error) {
        next(error);
    }
});

config.put("/:id", async (req, res, next) => {
    try {
        const config = await models.Configuration.findByPk(req.params.id);
        if (!config) {
            throw new Error(`config entry with id: ${req.params.id} not found`);
        }
        const newconfig = configSchema.parse(req.body);
        await config.update(newconfig);
        res.status(200).json(config);
    } catch (error) {
        next(error);
    }
});

config.delete("/:id", async (req, res, next) => {
    try {
        const config = await models.Configuration.findByPk(req.params.id);
        if (!config) {
            throw new Error(`config entry with id: ${req.params.id} not found`);
        }
        await config.destroy();
        res.status(204).send();
    } catch (error) {
        next(error);
    }
});

export default config;
