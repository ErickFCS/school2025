import models from "../../models/Index.js";
import { configSchema } from "../../types/configs.js";
import { Router } from "express";
import { z } from "zod";


const config = Router();

config.get("/:id", async (req, res, next) => {
    try {
        const configs = await models.Configuration.findAll({
            where: { espId: req.params.id }
        });
        res.status(200).json(configs);
    } catch (error) {
        next(error);
    }
});

config.post("/", async (req, res, next) => {
    try {
        const configs = z.array(configSchema).parse(req.body);
        await models.Configuration.bulkCreate(configs);
        res.status(201).send();
    } catch (error) {
        next(error);
    }
});

export default config;
